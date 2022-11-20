#include <handler.hpp>

Config::Config(const std::string& fileName = "client.cfg") {
    // TODO: конструктор конфига, принимающий на вход имя файла конфига 
}

std::string& Config::read() {
    // TODO: чтение форматированной строки конфига 
}

void Config::write(const std::string&) {
    // TODO: запись строки(конфига) в объект класса конфига
}


UrlToIpConverter::UrlToIpConverter(VPNContext vpnContext) {
    // TODO: конструктор класса-конвертера из списка url в IP лист 
}

void UrlToIpConverter::runConvert() {
    // TODO: метод, реализующий конвертацию url ссылок в ip лист
}

std::vector<std::string> UrlToIpConverter::nsRequest(std::string url) {
    // TODO: метод, запрашивающий по url ip лист
}

std::vector<OptionalUrl> UrlToIpConverter::getOptionalUrlList() {
    // TODO: метод, возвращающий вектор структур из ip листа и url
    // (т.е структуру со всеми необходимыми данными)
}


Config MakeConfigurationFiles::MakeServerConfig() {
    // TODO: создание конфига сервера
}

Config MakeConfigurationFiles::MakeClientConfig() {
    // TODO: создание конфига клиента
}


OVPNRunner::OVPNRunner() {
    // TODO: конструктор класса, работающего поверх OpenVPN
}

void OVPNRunner::RunOpenVPNServer() {
    // TODO: запуск сервера OpenVPN
}

void OVPNRunner::StopOpenVPNServer() {
    // TODO: остановка сервера OpenVPN
}

Config OVPNRunner::GetClientConfig() {
    // TODO: получение конфига клиента
}

Config OVPNRunner::GetServerConfig() {
    // TODO: получение конфига сервера
}

void VpnMsgHandler::handle(boost::asio::const_buffer msgBuffer) {
    // TODO: хэндлер, принимающий буффер с url в виде бит с сервера
}

Config VpnMsgHandler::reply() {
    // TODO: проброс клиентского конфига обратно на сервера
}

void VpnMsgHandler::inputAnalyze() {
    // TODO: разработка входных данных на сервер
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

VPNContext VpnMsgHandler::convertVpnMsgToVpnContext(boost::asio::const_buffer vpnMsg) {
    // TODO: метод конвертации буфера с сервера в VPNContext
}

std::vector<OptionalUrl> VpnMsgHandler::convertVpnContextToVpnList(const VPNContext& ) {
    // TODO: метод конвертации VPNContext в вектор наборов из url и Ip листов
}
