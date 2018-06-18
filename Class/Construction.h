#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__

#include "cocos2d.h"


/*@name  王笑天*/
/*建筑类，这里创建包含游戏建筑的Sprite*/

//建筑种类
enum ConstructionType{
	BASE,POWER,MINER,MILICAMP,TANKFAC,RADAR
};

class Construction : public cocos2d::Sprite 
{
public:
	/*创建建筑*/
	static Construction* creatWithType(ConstructionType type);

	bool initWithType(ConstructionType type);

	void ConstructionDestroy(Construction * construction);

	/*设置/得到建筑血量*/
	void setMaxHP(int Hp);
	int getHpNow() ;
	/*花费/产生金钱*/
	void setCostMon(int money);
	void setProMon(int money);
	int getProMon();
	/*消耗/产生能源*/
	void setCostPow(int power);
	void setProPow(int power);
	int getProPow();
	int getCostPow();


/***************************************建筑属性*********************************************/
private:

	int _Max_HP;                    /*建筑最大生命*/
	int _HPNow;                      /*建筑当前生命*/
	int _cost_money;             /*建造花费*/

	int _ProduceMoneyPerFrame;             /*产生金钱数目*/

	int _cost_power;              /*消耗电能*/

	int _produce_power;            /*产生电能*/



};
#endif //__CONSTRUCTION_H__
