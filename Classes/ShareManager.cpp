#include "ShareManager.h"
#include "Model\RouteInfo.h"

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

void ShareManager::orderRouteInfo(){
	CCArray* routes = CCArray::create();
	CCArray* routeInfo = ShareManager::getInstance()->getRouteInfo();
	int pointLen = routeInfo->count();
	for(int i=1;i<=pointLen;i++){
		CCString* targetPTName = CCString::createWithFormat("PT%d",i);
		for(int j=0;j<routeInfo->count();j++){
			RouteInfo* ri = (RouteInfo*)routeInfo->objectAtIndex(j);
			if(ri->pointName==targetPTName->getCString()){
				CCLog(ri->pointName.c_str());
				routeInfo->fastRemoveObjectAtIndex(j);
				routes->addObject(ri);
				break;
			}
		}
	}
	routes->retain();
	ShareManager::getInstance()->setRouteInfo(routes);
}