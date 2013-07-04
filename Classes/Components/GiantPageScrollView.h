#ifndef _GIANTPAGESCROLLVIEW_H_
#define _GIANTPAGESCROLLVIEW_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GiantPageScrollView:public CCLayer,public CCTableViewDataSource,public CCTableViewDelegate{
private:
	bool isInit;
	CCObject* target;
	SEL_MenuHandler selector;
	int currentIdx;
	CCPoint touchOffset;
public:
	CCSize tableSize;
	CCSize cellSize;
	int cellNum;
	CCArray* cells;
public:
	virtual void onEnter();
	virtual void registerWithTouchDispatcher();
	CREATE_FUNC(GiantPageScrollView);
	virtual void scrollViewDidScroll(CCScrollView* view){};
	virtual void scrollViewDidZoom(CCScrollView* view){};
	virtual void tableCellTouched(CCTableView* view,CCTableViewCell* cell);
	virtual bool init();
	virtual CCSize cellSizeForTable(CCTableView* view);
	virtual unsigned int numberOfCellsInTableView(CCTableView* view);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView* view, unsigned int idx);
	virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
	virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);

	virtual void showCellByInx(int idx,bool animate=true);

	unsigned int getCurrentIdx();
	void setTouchTarget(CCObject* target,SEL_MenuHandler selecotr);
};

#endif