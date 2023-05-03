#include <iostream>
#include<stdlib.h>//随机   
#include<time.h>//随机
#include<graphics.h>//图片操作的头文件
#include<conio.h>//getch的头文件     getch也是一个阻塞函数，没有按键时会等待按键
using namespace std;
IMAGE bk;
IMAGE birdp[2];
IMAGE down[2];
IMAGE up[2];
IMAGE End[2];
int g = 0;

void Draw();//把鸟和柱子放在一起画   
//加载图像
void loadRescource()
{
	loadimage(&bk, L"res/background.bmp",400,600);
	loadimage(birdp+0, L"res/bird.bmp", 48, 48);
	loadimage(birdp+1, L"res/birdy.bmp", 48, 48);
	loadimage(down+0, L"res/down.bmp");
	loadimage(down+1, L"res/downy.bmp");
	loadimage(up+0, L"res/up.bmp" );
	loadimage(up+1, L"res/upy.bmp");
	loadimage(End+0, L"res/end.bmp");
	loadimage(End+1, L"res/endy.bmp");
}

//描述鸟的数据
class Post
{
private:
	int x;
	int y;
	int speed;//左移的速度
	int sp;//中间的空隙 space
	int score = 0;
public:
	Post(int x, int y, int speed, int sp)
	{
		this->x = x;
		this->y = y;
		this->speed = speed;
		this->sp = sp;
	}
	int setx(int a)
	{
		x = a;
	}
	int sety(int a)
	{
		y = a;
	}
	int getx() {
		return x;
	}
	int gety() {
		return y;
	}
	int getsp() {
		return sp;
	}
	//1画两根柱子
	void DrawPost()
	{
		putimage(getx(), gety() + sp, up + 1, SRCAND);
		putimage(getx(), gety() + sp, up + 0, SRCPAINT);
		putimage(getx(), gety(), down + 1, SRCAND);
		putimage(getx(), gety(), down + 0, SRCPAINT);

	}
	//2柱子向左移动（到达左侧时重置）	
	void MovePost()
	{
		x = x - speed;
		//putimage(0, 0, &bk);
		//Sleep(25);
		if (x == (-52)) 
		{
			x = 288 + 26;
			y = -300 + rand() % 401;//实现y在-300到100之间随机生成
		}
			
		if (x == 70)//3柱子移动过鸟时加一分
			score += 1;
		//FlushBatchDraw();a
	}

	int getScore()//提取分数
	{
		return score;
	}

};


Post post(314, -300, 2, 500);


class Bird 
{
private:
	int x;
	int y;
	int speed;
public:
	Bird(int x, int y, int speed)
	{
		this->x = x;
		this->y = y;
		this->speed = speed;
	}
	void post1(Post& post)
	{
		post.MovePost();
	}
	int setx(int a)
	{
		x = a;
	}
	int sety(int a)
	{
		y = a;
	}
	int getx() {
		return x;
	}
	int gety() {
		return y;
	}
	int getspeed() {
		return speed;
	}
	//自动移动和手动移动
	void MoveBird() 
	{
		y = y + g;
		if(g<10)
		g = g + 1;
		Sleep(25);
		//休眠控制函数运行速度 类似delay
		//自由落体可以用循环改变休眠函数的参数，呈二次函数规律变化
		
	}
	
	//3控制鸟    kphit函数？？？有什么用
	void ControlBird() {
		//用不需要回车确认的getch函数实现，这个函数也不会把字符显示在屏幕上
		char userKey = '\0';//定义一个存储用户按键的变量
		userKey = _getch();
		if (userKey == 'w' || userKey == 'W' || userKey == 65)
		{
		
			for (speed=6; speed >= 0;speed--)
			{
				y = y - (speed * speed);
				putimage(0, 0, &bk);
				post.MovePost();
				Draw();//画一下鸟和柱子 但鸟上跃时柱子加速了 为什么呢？？？
				FlushBatchDraw();
				Sleep(25);
			}
		}
		g = 1;

	}
	//4碰撞销毁（碰上下边界）
	int HitEdge() 
	{
		if (y <= 0 || y >= 520 -20)
		{
			return 1;
		}
		else
			return 0;
	}

	void DrawBird() 
	{
		putimage(getx(), gety(), birdp+1, SRCAND);
		putimage(getx(), gety(), birdp+0, SRCPAINT);

	}
};
Bird bird(120, 10, 8);//创建鸟




void Draw()
{
	putimage(bird.getx(), bird.gety(), birdp + 1, SRCAND);
	putimage(bird.getx(), bird.gety(), birdp + 0, SRCPAINT);
	putimage(post.getx(), post.gety() + post.getsp(), up + 1, SRCAND);
	putimage(post.getx(), post.gety() + post.getsp(), up + 0, SRCPAINT);
	putimage(post.getx(), post.gety(), down + 1, SRCAND);
	putimage(post.getx(), post.gety(), down + 0, SRCPAINT);

}

//碰柱子结束
int HitPost()//
{
	if ((((bird.getx() + 32) >= (post.getx() )) && ((bird.getx() + 32) <= (post.getx()+52))&&(bird.gety()) <= (post.gety() + 320) )
	||  (((bird.getx() + 32) >= (post.getx())) && ((bird.getx() + 32) <= (post.getx() + 52)) && (bird.gety()+17) >= (post.gety() + 500))
	//||  ((bird.getx() + 32) >= (post.getx())   && (bird.getx() + 33) <= (post.getx()+52))&& (bird.gety()) == (post.gety() + 320)
	//||  ((bird.getx() + 32) >= (post.getx())   && (bird.getx() + 33) <= (post.getx()+52))&& (bird.gety()) == (post.gety() + 500)
		)
		return 1;
	else
		return 0;
}
//游戏结束
int gameover()
{
	if (bird.HitEdge()||HitPost())
	{
		cout << "游戏结束" << endl;
		cout << "得分为" << post.getScore() << endl;
		return 1;
	}
}


int main()
{
	srand((unsigned int)time(NULL));//用随机数操作柱子的y坐标实现随机出现空档
	initgraph(288, 600);//创建窗口
	BeginBatchDraw();//开始双缓冲
	loadRescource();
	while (1)//防止闪屏
	{
		putimage(0, 0, &bk);//把图片放到坐标位置
		Draw();
		bird.DrawBird();
		bird.MoveBird();
		post.DrawPost();
		post.MovePost();
		Sleep(25);
		FlushBatchDraw();
		if (_kbhit())//判断是否存在按键 如果存在按键 返回非零值
		{
			bird.ControlBird();
			
		}
		if (gameover())
			return 0;
		FlushBatchDraw();
		
	}
	EndBatchDraw();
	closegraph();//关闭窗口
	return 0;
}
