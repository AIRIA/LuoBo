#include "ShareManager.h"

ShareManager* ShareManager::_instance = 0;

ShareManager* ShareManager::getInstance(){
	if(!_instance){
		_instance = new ShareManager();
	}
	return _instance;
}

CCArray* ShareManager::getRouteInfo(){
	return this->routeInfo;
}

void ShareManager::setRouteInfo(CCArray* routeInfo){
	this->routeInfo = routeInfo;
}