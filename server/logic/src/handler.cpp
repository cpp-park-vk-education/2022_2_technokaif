#include <handler.hpp>

// -------------<Config>-----------

int Config::read() {
    // TODO(Ilya): чтение форматированной строки конфига

    file_ptr.open(_file_name);
    while (!file_ptr.eof()) {
        file_ptr >> buffer;
    }

    if (file_ptr.bad()) {
        std::cerr << "Bad config reading";
        return EXIT_FAILURE;
        file_ptr.close();
    }

    file_ptr.close();
    return EXIT_SUCCESS;
}

int Config::writeIpList(const std::string& ipList) {
    // TODO(Ilya): запись строки(конфига) в объект класса конфига

    file_ptr.open(_file_name);
    std::string buffer;
    while (std::getline(file_ptr, buffer) && buffer.compare("verb 3")) { }
    std::streampos pos = file_ptr.tellg();
    file_ptr.seekp(pos);
    file_ptr << ipList;

    if (file_ptr.bad()) {
        std::cerr << "Bad config writing";
        return EXIT_FAILURE;
        file_ptr.close();
    }

    file_ptr.close();
    return EXIT_SUCCESS;
}

// -------------<UrlToIpConverter>-----------

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

    // boost::regex pattern("/^(?:https?:\\/\\/)?(?:www\\.)?([^/]+)/");
    // boost::smatch result;
    // bool isMatchFound = boost::regex_match(url, result, pattern); 
    std::string host;
    const std::string header = "https://";
    int pos = url.find(header);
    if (pos == 0) {
        host = url.substr(header.size());
    } else {
        host = url;
    }
    // if (isMatchFound) { 
    //     host = result[0];
    // }

    std::vector<std::string> ipVector;
    // FILE* fp;
    // int status;
    std::string nslookup = "nslookup ";
    nslookup += (host + " | grep -oE '\\b[0-9]{1,3}(\\.[0-9]{1,3}){3}\\b' > ip.md");
    const char* command = const_cast<char*>(nslookup.c_str());
    // fp = popen(command, "r");
    std::system(command); 
    // if (fp == NULL) {
    //     std::cerr << "Error processing url in ip list" << std::endl;
    // }

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
    // status = pclose(fp);
    // if (status == -1) {
    //     std::cerr << "Error while closing convertion process" << std::endl;
    // }

    return ipVector;
}

std::vector<OptionalUrl> UrlToIpConverter::getOptionalUrlList(VPNContext vpnContext_) {
    // TODO(Ilya): метод, возвращающий вектор структур из ip листа и url
    // (т.е структуру со всеми необходимыми данными)

    vpnContext = vpnContext_;
    runConvert();
    return vpnList;
}

// -------------<MakeConfigurationFiles>-----------

Config MakeConfigurationFiles::MakeClientConfig(std::string name) {
    // TODO(Ilya): создание конфига клиента


    return Config("config");
}

void MakeConfigurationFiles::setMode(VPNMode vpnmode_) {
    vpnMode = vpnmode_;
}

void MakeConfigurationFiles::setIpList(std::vector<std::string> ipList) {
    optionalIpList = ipList;
}

void MakeConfigurationFiles::DeleteClientConfig(std::string name) {

}

// -------------<OVPNRunner>-----------

void OVPNRunner::generateName() {
    static char randomm[] = {
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g',
        'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '1', '2', '3', '4',
        '5', '6', '7', '8', '9', '0'
    };
 
    std::string result;
    for(size_t i = 0; i < 20; ++i)
        result += randomm[random() % 36];
 
    userName = result;
}

OVPNRunner::OVPNRunner() {
    generateName();
}

int OVPNRunner::RunOpenVPNServer() {
    // TODO(Ilya): запуск сервера OpenVPN


    return EXIT_SUCCESS;
}

int OVPNRunner::RunOpenVPNServerWithOptions(std::vector<std::string>) {
    // TODO(Ilya): запуск сервера OpenVPN с параметрами

    return EXIT_SUCCESS;
}

int OVPNRunner::StopOpenVPNServer() {
    // TODO(Ilya): остановка сервера OpenVPN

    confFilesMaker.setMode(stopped);
    confFilesMaker.DeleteClientConfig(userName);
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

    return ovpnRunner.GetClientConfig();
}

void VpnMsgHandler::inputAnalyze(std::string msgBuffer) {
    // TODO(Ilya): разработка входных данных на сервер

    convertVpnMsgToVpnContext(msgBuffer);
    convertVpnContextToVpnList();
}

void VpnMsgHandler::convertVpnListToIpList() {
    for (auto ipL : this->_vpnList) {
        for (auto ip : ipL.ipList) {
           _ipList.push_back(ip);
        }
    }
}

void VpnMsgHandler::logic() {
    if (this->_vpnContext.state == stopped) {
        ovpnRunner.StopOpenVPNServer();
    } else if (this->_vpnContext.state == runTotal) {
        ovpnRunner.RunOpenVPNServer();
    } else {
        ovpnRunner.RunOpenVPNServerWithOptions(_ipList);
    }
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
    VPNContext context = {runOptional, {"google.com", "https://github.io"}};
    UrlToIpConverter converter;
    std::vector<OptionalUrl> ipList;
    ipList = converter.getOptionalUrlList(context);
    for (auto elem : ipList) {
        for (auto ip : elem.ipList) {
            std::cout << ip << std::endl;
        }
    }
}
