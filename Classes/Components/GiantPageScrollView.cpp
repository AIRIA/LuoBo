#include "GiantPageScrollView.h"
#include "../VisibleRect.h"
enum{
	pTableViewInd
};
void GiantPageScrollView::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void GiantPageScrollView::onEnter(){
	CCLayer::onEnter();
	if(!isInit){
		CCTableView* pTable = CCTableView::create(this,tableSize);
		CCPoint point = pTable->getPosition();
		CCSize s = pTable->getContentSize();
		pTable->setDirection(kCCScrollViewDirectionHorizontal);
		pTable->setPosition(CCPointZero);
		pTable->setDelegate(this);
		pTable->setTag(pTableViewInd);
		this->addChild(pTable);
		pTable->reloadData();
		isInit = true;
	}
	
}

bool GiantPageScrollView::init(){
	if(!CCLayer::init()){
		return false;
	}
	setTouchEnabled(true);
	ignoreAnchorPointForPosition(false);
	isInit = false;
	target = NULL;
	currentIdx = 0;
	return true;
}

unsigned int GiantPageScrollView::getCurrentIdx(){
	return currentIdx;
}

void GiantPageScrollView::setTouchTarget(CCObject* target,SEL_MenuHandler selector){
	this->target = target;
	this->selector = selector;
}

bool GiantPageScrollView::ccTouchBegan(CCTouch* touch,CCEvent* event){
	CCTableView* tv = (CCTableView*)getChildByTag(pTableViewInd);
	touchOffset = tv->getContentOffset();
	return true;
}

#define CELLSIZE 960
void GiantPageScrollView::ccTouchEnded(CCTouch* touch,CCEvent* event){
	CCTableView* tv = (CCTableView*)getChildByTag(pTableViewInd);
	CCPoint offset = tv->getContentOffset();
	tv->unscheduleAllSelectors();
	int idx = abs(offset.x/CELLSIZE);
	//new
	float moveX = touchOffset.x - offset.x;
	if(abs(moveX)>50){
		if(moveX>0){
			offset.x = -960*(idx+1);
		}else{
			offset.x = -960*(idx);
		}
	}else{
		tv->setContentOffset(touchOffset,true);
		return;
	}

	if(offset.x >0){
		offset.x = 0;
	}
	if(offset.x < -1*(960*(cellNum-1))){
		offset.x = -960*(cellNum-1);
	}
	tv->setContentOffset(offset,true);
}

CCSize GiantPageScrollView::cellSizeForTable(CCTableView* tableView){
	return cellSize;
}

unsigned int GiantPageScrollView::numberOfCellsInTableView(CCTableView* tableView){
	return cellNum;
}

CCTableViewCell* GiantPageScrollView::tableCellAtIndex(CCTableView* table,unsigned int idx){
	CCTableViewCell* cell = table->dequeueCell();
	CCNode* node = (CCNode*)cells->objectAtIndex(idx);
	node->setParent(NULL);
	if(!cell){
		cell = new CCTableViewCell();
		cell->autorelease();
		cell->addChild(node);
		
	}else{
		cell->removeAllChildren();
		cell->addChild(node);
	}
	return cell;
}

void GiantPageScrollView::tableCellTouched(CCTableView* view,CCTableViewCell* cell){
	currentIdx = cell->getIdx();
	if(target!=NULL){
		(target->*selector)(this);
	}
}

void GiantPageScrollView::showCellByInx(int idx,bool animate){
	currentIdx = idx;
	CCNode* childNode = getChildByTag(pTableViewInd);
	CCTableView* tv = (CCTableView*)childNode;
	CCPoint offset = tv->getContentOffset();
	offset.x = -cellSize.width*idx;
	tv->setContentOffset(offset,animate);
}