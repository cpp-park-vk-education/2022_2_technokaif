#include <handler.hpp>

// -------------<Config>-----------

int Config::preRead() {
  file_ptr.open(_file_name);
  if (!file_ptr.is_open()) {
    std::cerr << "Bad config reading";
    return EXIT_FAILURE;
  }

  std::string buf;
  this->buffer = "";
  while (std::getline(file_ptr, buf)) {
    buffer += (buf + "\n");
  }

  if (file_ptr.bad()) {
    std::cerr << "Bad config reading";
    return EXIT_FAILURE;
    file_ptr.close();
  }

  file_ptr.close();
  return EXIT_SUCCESS;
}

int Config::read() {
  // TODO(Ilya): чтение форматированной строки конфига

  std::stringstream ss;
  for (auto iter = buffer.cbegin(); iter != buffer.cend(); ++iter) {
    ss << *iter;
  }

  nlohmann::json j;
  std::string buf;
  while (std::getline(ss, buf)) {
    j["config"].push_back(buf);
  }

  buffer = j.dump();

  return EXIT_SUCCESS;
}

int Config::writeIpList(const std::string &ipList) {
  // TODO(Ilya): запись строки(конфига) в объект класса конфига

  std::stringstream ss;
  for (auto iter = buffer.cbegin(); iter != buffer.cend(); ++iter) {
    ss << *iter;
  }

  std::string buf;
  std::string startBuffer = "";
  while (std::getline(ss, buf) && (buf.compare("verb 3") != 0)) {
    startBuffer += (buf + "\n");
  }

  std::string endBuffer = "";
  while (std::getline(ss, buf)) {
    endBuffer += (buf + "\n");
  }

  buffer = startBuffer + ipList + endBuffer;
  return EXIT_SUCCESS;
}

// -------------<UrlToIpConverter>-----------

void UrlToIpConverter::runConvert() {
  // TODO(Ilya): метод, реализующий конвертацию url ссылок в ip лист
  
  if (vpnContext.state != RUNNING || vpnContext.mode != OPTIONAL) {
    return;
  }

  for (const auto &url : vpnContext.urlList) {
    this->vpnList.push_back({url, nsRequest(url)});
  }
}

std::vector<std::string> UrlToIpConverter::nsRequest(std::string url) {
  // TODO(Ilya): метод, запрашивающий по url ip лист

  std::string host;
  const std::string header = "https://";
  int pos = url.find(header);
  if (pos == 0) {
    host = url.substr(header.size());
  } else {
    host = url;
  }

  std::vector<std::string> ipVector;
  std::string nslookup = "nslookup ";
  nslookup +=
      (host + " | grep -oE '\\b[0-9]{1,3}(\\.[0-9]{1,3}){3}\\b' > ip.md");
  const char *command = const_cast<char *>(nslookup.c_str());
  std::system(command);

  std::ifstream f_ptr("ip.md");
  if (f_ptr.bad()) {
    std::cerr << "Error processing url in ip list" << std::endl;
  }

  int counter = 0;
  while (!f_ptr.eof()) {
    char buf[MAX_BUFFER_SIZE];
    f_ptr.getline(buf, MAX_BUFFER_SIZE);
    if (counter > 1) {
      ipVector.push_back(std::string(buf));
    }

    ++counter;
  }

  if (f_ptr.bad()) {
    std::cerr << "Error processing url in ip list" << std::endl;
  }

  return ipVector;
}

std::vector<OptionalUrl>
UrlToIpConverter::getOptionalUrlList(VPNContext vpnContext_) {
  // TODO(Ilya): метод, возвращающий вектор структур из ip листа и url
  // (т.е структуру со всеми необходимыми данными)

  vpnContext = vpnContext_;
  runConvert();
  return vpnList;
}

// -------------<MakeConfigurationFiles>-----------

Config *MakeConfigurationFiles::MakeClientConfig(std::string name) {
  std::string com = "bash /2022_2_technokaif/server/logic/src/openVpnRun.sh";
  char *command = const_cast<char *>(com.c_str());
  boost::process::opstream in;
  boost::process::child c(command, boost::process::std_in < in);

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2000ms);

  com = "1";
  command = const_cast<char *>(com.c_str());

  in << command << std::endl;
  std::this_thread::sleep_for(2000ms);

  command = const_cast<char *>(name.c_str());
  in << command << std::endl;
  std::this_thread::sleep_for(5000ms);

  c.terminate();

  std::string fileName = "/root/" + name + ".ovpn";

  Config *clientConfig = new Config(fileName);
  clientConfig->preRead();
  if (state == RUNNING && vpnMode == OPTIONAL) {
    std::string ipList = "route-nopull\n";
    for (auto ip : optionalIpList) {
      if (ip == "") {
        continue;
      }

      ipList += ("route " + ip + " 255.255.255.255\n");
    }

    clientConfig->writeIpList(ipList);
  }

  clientConfig->read();
  return clientConfig;
}

void MakeConfigurationFiles::setMode(VPNMode vpnmode_) { vpnMode = vpnmode_; }
void MakeConfigurationFiles::setState(RunStatus status) { state = status; }

void MakeConfigurationFiles::setIpList(std::vector<std::string> ipList) {
  optionalIpList = ipList;
}

void MakeConfigurationFiles::DeleteClientConfig(std::string name) {
  std::string com = "bash /2022_2_technokaif/server/logic/src/openVpnRun.sh";
  char *command = const_cast<char *>(com.c_str());
  boost::process::opstream in;
  boost::process::ipstream out;
  std::future<std::vector<char>> output;

  boost::asio::io_service svc;
  boost::process::child c(
      command, boost::process::std_in<in, boost::process::std_out> output, svc);
  svc.run();
  {
    auto raw = output.get();
    std::vector<std::string> data;
    std::string line;
    boost::iostreams::stream_buffer<boost::iostreams::array_source> sb(
        raw.data(), raw.size());
    std::istream is(&sb);
    char number;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2000ms);

    com = "2";
    command = const_cast<char *>(com.c_str());

    in << command << std::endl;
    std::this_thread::sleep_for(2000ms);

    while (std::getline(is, line) && !line.empty()) {
      size_t pos = line.find(name);
      if (pos != std::string::npos) {
        number = line.at(0);
      }
    }

    in << number << std::endl;
    std::this_thread::sleep_for(5000ms);
  }

  c.terminate();
}

// -------------<OVPNRunner>-----------

void OVPNRunner::generateName() {
  static char randomm[] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o',
                           'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k',
                           'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '1',
                           '2', '3', '4', '5', '6', '7', '8', '9', '0'};

  std::string result;

  std::srand(
      std::time(nullptr)); // use current time as seed for random generator
  for (size_t i = 0; i < 10; ++i)
    result += randomm[std::rand() % 36];

  userName = result;
}

OVPNRunner::OVPNRunner() { generateName(); }

int OVPNRunner::RunOpenVPNServer() {
  // TODO(Ilya): запуск сервера OpenVPN

  confFilesMaker.setMode(TOTAL);
  confFilesMaker.setState(RUNNING);
  clientConfig = confFilesMaker.MakeClientConfig(userName);
  return EXIT_SUCCESS;
}

int OVPNRunner::RunOpenVPNServerWithOptions(std::vector<std::string> ipList) {
  // TODO(Ilya): запуск сервера OpenVPN с параметрами

  confFilesMaker.setMode(OPTIONAL);
  confFilesMaker.setState(RUNNING);
  clientConfig = confFilesMaker.MakeClientConfig(userName);
  return EXIT_SUCCESS;
}

int OVPNRunner::StopOpenVPNServer() {
  // TODO(Ilya): остановка сервера OpenVPN

  confFilesMaker.setState(STOPPED);
  // confFilesMaker.DeleteClientConfig(userName);
  return EXIT_SUCCESS;
}

std::string OVPNRunner::GetClientConfig() {
  // TODO(Ilya): получение конфига клиента

  return clientConfig->getConfig();
}

// -------------<VpnMsgHandler>-----------

void VpnMsgHandler::handle(std::string msgBuffer) {
  // TODO(Ilya): хэндлер, принимающий буффер с url в виде бит с сервера

  inputAnalyze(msgBuffer);
}

std::string VpnMsgHandler::reply() {
  // TODO(Ilya): проброс клиентского конфига обратно на сервер
  if (_vpnContext.state == STOPPED) {
    return "";
  }

  return ovpnRunner.GetClientConfig();
}

void VpnMsgHandler::inputAnalyze(std::string msgBuffer) {
  // TODO(Ilya): разработка входных данных на сервер

  convertVpnMsgToVpnContext(msgBuffer);
  convertVpnContextToVpnList();
  convertVpnListToIpList();
  logic();
}

void VpnMsgHandler::convertVpnListToIpList() {
  if (_vpnContext.state != RUNNING || _vpnContext.mode != OPTIONAL) {
    return;
  }

  for (auto ipL : this->_vpnList) {
    for (auto ip : ipL.ipList) {
      _ipList.push_back(ip);
    }
  }
}

void VpnMsgHandler::logic() {
  if (this->_vpnContext.state == STOPPED) {
    ovpnRunner.StopOpenVPNServer();
  } else if (this->_vpnContext.mode == TOTAL) {
    ovpnRunner.RunOpenVPNServer();
  } else {
    ovpnRunner.RunOpenVPNServerWithOptions(_ipList);
  }
}

void VpnMsgHandler::setVpnContext(const VPNContext &vpnContext_) {
  this->_vpnContext = vpnContext_;
}

void VpnMsgHandler::setVpnList(const std::vector<OptionalUrl> &vpnList_) {
  this->_vpnList = vpnList_;
}

void VpnMsgHandler::convertVpnMsgToVpnContext(std::string vpnMsg) {
  // TODO(Ilya): метод конвертации буфера с сервера в VPNContext

  nlohmann::json j = nlohmann::json::parse(vpnMsg);
  _vpnContext.mode = j["mode"].get<VPNMode>();
  _vpnContext.state = j["state"].get<RunStatus>();
  if (_vpnContext.state == RUNNING && _vpnContext.mode == OPTIONAL) {
    j["urlList"].get_to<std::vector<std::string>>(_vpnContext.urlList);
  }
}

void VpnMsgHandler::convertVpnContextToVpnList() {
  // TODO(Ilya): метод конвертации VPNContext в вектор наборов из url и Ip
  // листов

  if (_vpnContext.state != RUNNING || _vpnContext.mode != OPTIONAL) {
    return;
  } 

  _vpnList = urlConverter.getOptionalUrlList(_vpnContext);
}

int main() {
  VPNContext context1 = {OPTIONAL, RUNNING, {"yandex.ru", "https://google.com"}};
  VPNContext context2 = {OPTIONAL, STOPPED, {""}};

  nlohmann::json j{};

  j["mode"] = context1.mode;
  j["state"] = context1.state;
  j["urlList"] = context1.urlList;
  std::string input = j.dump();
  VpnMsgHandler handler;
  handler.handle(input);

  std::string output = handler.reply();
  std::cout << output;

  j["mode"] = context1.mode;
  j["state"] = context2.state;
  j["urlList"] = context2.urlList;
  input = j.dump();
  handler.handle(input);

  output = handler.reply();
  std::cout << output;
}
