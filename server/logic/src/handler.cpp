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
}

std::vector<std::string> UrlToIpConverter::nsRequest(std::string url) {
    // TODO(Ilya): метод, запрашивающий по url ip лист

    std::vector<std::string> ipVector;
    ipVector.push_back(url);
    return ipVector;
}

std::vector<OptionalUrl> UrlToIpConverter::getOptionalUrlList() {
    // TODO(Ilya): метод, возвращающий вектор структур из ip листа и url
    // (т.е структуру со всеми необходимыми данными)

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

void VpnMsgHandler::handle(char* msgBuffer) {
    // TODO(Ilya): хэндлер, принимающий буффер с url в виде бит с сервера

    inputAnalyze(msgBuffer);
}

Config VpnMsgHandler::reply() {
    // TODO(Ilya): проброс клиентского конфига обратно на сервера

    return ovpnRunner.GetClientConfig();
}

void VpnMsgHandler::inputAnalyze(char msgBuffer[BUFF_SIZE]) {
    // TODO(Ilya): разработка входных данных на сервер

    vpnContext = convertVpnMsgToVpnContext(msgBuffer);
}

void VpnMsgHandler::setVpnContext(const VPNContext& vpnContext_) {
    this->vpnContext = vpnContext_;
}

void VpnMsgHandler::setVpnMode(const VPNMode& vpnMode_) {
    vpnMode = vpnMode_;
}

void VpnMsgHandler::setVpnList(const std::vector<OptionalUrl>& vpnList_) {
    vpnList = vpnList_;
}

VPNContext VpnMsgHandler::convertVpnMsgToVpnContext(char vpnMsg[BUFF_SIZE]) {
    // TODO(Ilya): метод конвертации буфера с сервера в VPNContext

    VPNContext vpnContext;
    vpnContext.urlList.push_back(std::string(vpnMsg));
    return VPNContext();
}

std::vector<OptionalUrl> VpnMsgHandler::convertVpnContextToVpnList(const VPNContext& vpnContext_) {
    // TODO(Ilya): метод конвертации VPNContext в вектор наборов из url и Ip листов

    std::vector<OptionalUrl> ipUrlLists;
    OptionalUrl ipUrlList;
    ipUrlList.url = vpnContext_.urlList.at(0);
    ipUrlLists.push_back(OptionalUrl());

    return ipUrlLists;
}
