main:administrator.o balance.o box.o calculator.o check.o color.o data.o file.o goods.o insert.o login.o mainpage.o menu.o order.o register.o trolley.o update.o user.o
	g++ *.o -o $@
balance.o:balance.cpp
	g++ -c balance.cpp -o balance.o
check.o:check.cpp
	g++ -c check.cpp -o check.o
administrator.o:administrator.cpp
	g++ -c administrator.cpp -o administrator.o
box.o:box.cpp
	g++ -c box.cpp -o box.o
calculator.o:calculator.cpp
	g++ -c calculator.cpp -o calculator.o
color.o:color.cpp
	g++ -c color.cpp -o color.o
data.o:data.cpp
	g++ -c data.cpp -o data.o
file.o:file.cpp
	g++ -c file.cpp -o file.o
goods.o:goods.cpp
	g++ -c goods.cpp -o goods.o
insert.o:insert.cpp
	g++ -c insert.cpp -o insert.o
login.o:login.cpp
	g++ -c login.cpp -o login.o
mainpage.o:mainpage.cpp
	g++ -c mainpage.cpp -o mainpage.o
menu.o:menu.cpp
	g++ -c menu.cpp -o menu.o
order.o:order.cpp
	g++ -c order.cpp -o order.o
register.o:register.cpp
	g++ -c register.cpp -o register.o
trolley.o:trolley.cpp
	g++ -c trolley.cpp -o trolley.o
update.o:update.cpp
	g++ -c update.cpp -o update.o
user.o:user.cpp
	g++ -c user.cpp -o user.o
clean:
	rm -f *.o main