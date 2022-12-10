#include <handler.hpp>

Config::Config() {
    file_ptr.open("config.cfg");
}

Config::~Config() {
    file_ptr.close();
}

Config::Config(const Config& obj) {
    // TODO(Ilya): конструктор копирования конфига
    this->buffer = obj.buffer;
}

Config::Config(std::string fileName) {
    // TODO(Ilya): конструктор конфига, принимающий на вход имя файла конфига

    file_ptr.open(fileName);
}

std::string& Config::read() {
    // TODO(Ilya): чтение форматированной строки конфига

    file_ptr >> buffer;
    return buffer;
}

void Config::write(const std::string&) {
    // TODO(Ilya): запись строки(конфига) в объект класса конфига
}


void UrlToIpConverter::runConvert() {
    // TODO(Ilya): метод, реализующий конвертацию url ссылок в ip лист
    if (vpnContext.state != runOptional) {
        return;
    }

    for (const auto &url : vpnContext.urlList) {
        this->vpnList.push_back({url, nsRequest(url)});
    }
}

std::vector<std::string> UrlToIpConverter::nsRequest(std::string url) {
    // TODO(Ilya): метод, запрашивающий по url ip лист

    boost::regex pattern("/^(?:https?:\\/\\/)?(?:www\\.)?([^/]+)/");
    boost::smatch result;
    bool isMatchFound = boost::regex_match(url, result, pattern); 
    std::string host;
    if (isMatchFound) { 
        host = result[0];
    }

    std::vector<std::string> ipVector;
    FILE* fp;
    int status;
    const std::string nslookup = "nslookup google.com | grep -oE '\\b[0-9]{1,3}(\\.[0-9]{1,3}){3}\\b";
    const char* command = const_cast<char*>(nslookup.c_str());
    fp = popen(command, "r");
    if (fp == NULL) {
        std::cerr << "Error processing url in ip list" << std::endl;
    }

    int MAX_BUFFER_SIZE = 30;
    int counter = 0;
    while (!feof(fp)) {
        char buf[MAX_BUFFER_SIZE];
        fgets(buf, MAX_BUFFER_SIZE, fp);
        if (counter > 1) {
            ipVector.push_back(std::string(buf));
        }

        ++counter;
    }


    status = pclose(fp);
    if (status == -1) {
        std::cerr << "Error while closing convertion process" << std::endl;
    }

    return ipVector;
}

std::vector<OptionalUrl> UrlToIpConverter::getOptionalUrlList(VPNContext vpnContext_) {
    // TODO(Ilya): метод, возвращающий вектор структур из ip листа и url
    // (т.е структуру со всеми необходимыми данными)

    runConvert();
    return vpnList;
}


Config MakeConfigurationFiles::MakeServerConfig() {
    // TODO(Ilya): создание конфига сервера

    return Config("config");
}

Config MakeConfigurationFiles::MakeClientConfig() {
    // TODO(Ilya): создание конфига клиента

    return Config("config");
}


OVPNRunner::OVPNRunner() {
    // TODO(Ilya): конструктор класса, работающего поверх OpenVPN
}

int OVPNRunner::RunOpenVPNServer() {
    // TODO(Ilya): запуск сервера OpenVPN

    return EXIT_SUCCESS;
}

int OVPNRunner::StopOpenVPNServer() {
    // TODO(Ilya): остановка сервера OpenVPN

    return EXIT_SUCCESS;
}

Config OVPNRunner::GetClientConfig() {
    // TODO(Ilya): получение конфига клиента

    return clientConfig;
}

Config OVPNRunner::GetServerConfig() {
    // TODO(Ilya): получение конфига сервера

    return serverConfig;
}

void VpnMsgHandler::handle(std::string msgBuffer) {
    // TODO(Ilya): хэндлер, принимающий буффер с url в виде бит с сервера

    inputAnalyze(msgBuffer);
}

Config VpnMsgHandler::reply() {
    // TODO(Ilya): проброс клиентского конфига обратно на сервера

    return ovpnRunner.GetClientConfig();
}

void VpnMsgHandler::inputAnalyze(std::string msgBuffer) {
    // TODO(Ilya): разработка входных данных на сервер

    convertVpnMsgToVpnContext(msgBuffer);
    convertVpnContextToVpnList();
}

void VpnMsgHandler::setVpnContext(const VPNContext& vpnContext_) {
    this->_vpnContext = vpnContext_;
}

void VpnMsgHandler::setVpnList(const std::vector<OptionalUrl>& vpnList_) {
    this->_vpnList = vpnList_;
}

void VpnMsgHandler::convertVpnMsgToVpnContext(std::string vpnMsg) {
    // TODO(Ilya): метод конвертации буфера с сервера в VPNContext

    nlohmann::json j = nlohmann::json::parse(vpnMsg);
    _vpnContext.state = j["state"].get<VPNMode>();
    j["urlList"].get_to<std::vector<std::string>>( _vpnContext.urlList);
}

void VpnMsgHandler::convertVpnContextToVpnList() {
    // TODO(Ilya): метод конвертации VPNContext в вектор наборов из url и Ip листов

    _vpnList = urlConverter.getOptionalUrlList(_vpnContext);
}

int main() {
    VPNContext context = {runOptional, {"google.com", "https://google.com"}};
    UrlToIpConverter converter;
    std::vector<OptionalUrl> ipList;
    ipList = converter.getOptionalUrlList(context);
    for (auto elem : ipList) {
        for (auto ip : elem.ipList) {
            std::cout << ip << std::endl;
        }
    }
}
