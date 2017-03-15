#define DARWIN_FORCE_BUILTIN
#include "./darwin/headers/darwin.hpp"
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <utility>
int main()
{
	darwin::runtime.load("./darwin.module");
	auto pic=darwin::runtime.get_drawable();
	darwin::sync_clock clock(30);
	darwin::pixel p('@',true,false,darwin::colors::blue,darwin::colors::white);
	darwin::pixel pix('-',true,false,darwin::colors::blue,darwin::colors::white);
	darwin::pixel pixel('#',true,false,darwin::colors::white,darwin::colors::white);
	darwin::pixel pixel1(' ',true,false,darwin::colors::black,darwin::colors::black);
	darwin::pixel die(' ',true,false,darwin::colors::red,darwin::colors::red);
	darwin::pixel win(' ',true,false,darwin::colors::green,darwin::colors::green);
	int x=0;
	int y=0;
	int c=9;
	int d=0;
	int x1=0;
	bool lose=true;
	std::vector<std::pair<int,int>> bz(10);
	std::default_random_engine e(time(nullptr));
	while(true) {
		clock.reset();
		darwin::runtime.fit_drawable();
		pic->clear();
		if(d<10) {
			std::uniform_int_distribution<int> u1(2,pic->get_width()-3);
			std::uniform_int_distribution<int> u2(2,pic->get_height()-4);
			int x2,y2;
			x2=u1(e);
			y2=u2(e);
			bz[d].first=x2;
			bz[d].second=y2;
			++d;
			if(d==10)
				for(int i=0; i<10; ++i) {
					std::pair<int,int> c=bz[i];
					for(int v=0; v<10; ++v)
						if(bz[v]==c&&i!=v)
							--d;
				}
			continue;
		}
		for(int i=0; i<10; ++i)
			if(bz[i].first>=0)
				pic->draw_pixel(bz[i].first,bz[i].second,pixel);
		int a=pic->get_width();
		int b=pic->get_height();
		int y1=b-1;
		int length;
		if(a%3==0)
			length=a/3;
		else if(a%3==1)
			length=(a-1)/3;
		else if(a%3==2)
			length=(a+1)/3;
		if(darwin::runtime.is_kb_hit()&&lose) {
			switch(darwin::runtime.get_kb_hit()) {
			case'a':
					if(x1>=1)
						--x1;
				break;
			case'd':
					if(x1+length<a)
						++x1;
				break;
			}
		}
		pic->draw_line(x1,y1,x1+length-1,y1,pix);
		if(c==9&&lose) {
			++x;
			++y;
			pic->draw_pixel(x,y,p);
			if(x==(a-1))
				c=7;
			if((x>=x1)&&(x<(x1+length))&&(y+1==y1))
				c=3;
			if((x+1==x1)&&(y+1==y1))
				c=1;
			if((x>=x1)&&((x+1)==(x1+length))&&(y+1==y1)&&x==(a-1))
				c=1;
			for(int i=0; i<10; ++i) {
				int count=0;
				if((bz[i].first==(x+1))&&(bz[i].second==(y+1))) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x+1,y+1,pixel1);
					c=1;
				}
				if((bz[i].first==(x+1))&&(bz[i].second==y)) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x+1,y,pixel1);
					c=7;
					++count;
				}
				if((bz[i].first==x)&&(bz[i].second==(y+1))) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x,y+1,pixel1);
					c=3;
					++count;
				}
				if(count==2)
					c=1;
			}
			if(y>=b)
				lose=false;
			darwin::runtime.update_drawable();
			continue;
		}
		if(c==3&&lose) {
			++x;
			--y;
			pic->draw_pixel(x,y,p);
			if(y==0)
				c=9;
			if(x==(a-1))
				c=1;
			if(x==(a-1)&&y==0)
				c=7;
			for(int i=0; i<10; ++i) {
				int count=0;
				if((bz[i].first==(x+1))&&(bz[i].second==(y-1))) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x+1,y-1,pixel1);
					c=7;
				}
				if((bz[i].first==(x+1))&&(bz[i].second==y)) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x+1,y,pixel1);
					c=1;
					++count;
				}
				if((bz[i].first==x)&&(bz[i].second==(y-1))) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x,y-1,pixel1);
					c=9;
					++count;
				}
				if(count==2)
					c=7;
			}
			if(y>=b)
				lose=false;
			darwin::runtime.update_drawable();
			continue;
		}
		if(c==1&&lose) {
			--x;
			--y;
			pic->draw_pixel(x,y,p);
			if(x==0)
				c=3;
			if(y==0)
				c=7;
			if(x==0&&y==0)
				c=9;
			for(int i=0; i<10; ++i) {
				int count=0;
				if((bz[i].first==(x-1))&&(bz[i].second==(y-1))) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x-1,y-1,pixel1);
					c=9;
				}
				if((bz[i].first==(x-1))&&(bz[i].second==(y))) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x-1,y,pixel1);
					c=3;
					++count;
				}
				if((bz[i].first==(x))&&(bz[i].second==(y-1))) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x,y-1,pixel1);
					c=7;
					++count;
				}
				if(count==2)
					c=9;
			}
			if(y>=b)
				lose=false;
			darwin::runtime.update_drawable();
			continue;
		}
		if(c==7&&lose) {
			--x;
			++y;
			pic->draw_pixel(x,y,p);
			if(x==0)
				c=9;
			if((x>=x1)&&((x)<(x1+length))&&((y+1)==y1))
				c=1;
			if((x==x1+length)&&((y+1)==y1))
				c=3;
			if((x==x1)&&((x)<(x1+length))&&((y+1)==y1)&&x==0)
				c=3;
			for(int i=0; i<10; ++i) {
				int count=0;
				if((bz[i].first==(x-1))&&(bz[i].second==(y+1))) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x-1,y+1,pixel1);
					c=3;
				}
				if((bz[i].first==(x-1))&&(bz[i].second==(y))) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x-1,y,pixel1);
					c=9;
					++count;
				}
				if((bz[i].first==(x))&&(bz[i].second==(y+1))) {
					bz[i].first=-1;
					bz[i].second=-1;
					pic->draw_pixel(x,y+1,pixel1);
					c=1;
					++count;
				}
				if(count==2)
					c=3;
			}
			if(y>=b)
				lose=false;
		}
		int count=0;
		for(int i=0; i<10; ++i)
			if(bz[i].first==-1)
				++count;
		if(count==10)
			pic->fill(win);
		if(!lose)
			pic->fill(die);
		darwin::runtime.update_drawable();
		clock.sync();
	}
	return 0;
}