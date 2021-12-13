--DTKZQ.VHD
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
ENTITY Vhdl1 IS
PORT(CLKIN:IN STD_LOGIC;   --2 Hz时钟输入信号
       UPIN:IN STD_LOGIC;     	--楼层上升请求键
       DOWNIN:IN STD_LOGIC; 	--楼层下降请求键
       ST_CH:IN STD_LOGIC;   	
                                   --结合DIRECT完成楼层选择的键入
       CLOSE:IN STD_LOGIC;   	--提前关门输入键
       DELAY:IN STD_LOGIC;   	--延迟关门输入键
       RUN_STOP:IN STD_LOGIC;	--电梯运行的开关键
       LAMP:OUT STD_LOGIC;  	--电梯运行或停止指示键
RUN_WAIT:OUT STD_LOGIC_VECTOR(3 DOWNTO 0); 
	--结合LAMP指示电梯运行或等待时间
       ST_OUT:OUT STD_LOGIC_VECTOR(3 DOWNTO 0);  	--电梯所在楼层指示数码管
       DIRECT:OUT STD_LOGIC_VECTOR(3 DOWNTO 0));  	--楼层选择指示数码管
 END ENTITY Vhdl1;
ARCHITECTURE ART OF Vhdl1 IS
SIGNAL UR,DR:STD_LOGIC_VECTOR(16 DOWNTO 1);      	
--上升或下降楼层请求寄存器
SIGNAL DIR,LIFTOR:STD_LOGIC_VECTOR(3 DOWNTO 0);  	
--楼选指示及楼层数计数器
SIGNAL WAI_T:STD_LOGIC_VECTOR(2 DOWNTO 0);       	
--运行或等待计数器
SIGNAL DIVID,HAND:STD_LOGIC;                     
	--时钟2分频和楼选复位变量
SIGNAL LADD:STD_LOGIC_VECTOR(1 DOWNTO 0);       	
--电梯运行状态变量
SIGNAL CLOSEX,DELAYX,LAMP0:STD_LOGIC;           
--提前关门及延迟变量 
BEGIN 
--内部信号值的输出
DIRECT<=DIR+1;
 ST_OUT<=LIFTOR+1;
 RUN_WAIT<='0'&WAI_T;
 P0:PROCESS(CLKIN) IS
  BEGIN
  IF (CLKIN'EVENT AND CLKIN='1') THEN
    LAMP<=LADD(1);
  END IF;
END PROCESS P0;
HAND<=WAI_T(2)AND (NOT WAI_T(1))AND WAI_T(0);
CLOSEX<=CLOSE AND (NOT LADD(1));
DELAYX<=DELAY AND (NOT LADD(1));

--分频及楼选信号产生进程
P1:PROCESS(CLKIN)
BEGIN
IF (CLKIN'EVENT AND CLKIN='1') THEN
    DIVID<=NOT DIVID;
    IF (DIR="1111") THEN DIR<="0000";
    ELSE DIR<=DIR+1;
    END IF;
  END IF;
END PROCESS;
--楼层请求寄存器的置位与复位进程
P2:PROCESS(UR, DR, UPIN, DOWNIN, ST_CH, LIFTOR, WAI_T, RUN_STOP, HAND)
 VARIABLE NUM,T:INTEGER RANGE 1 TO 16 ;
 BEGIN
   NUM:=CONV_INTEGER(LIFTOR)+1;
   T:=CONV_INTEGER(DIR)+1;
   IF (RUN_STOP='1') THEN
IF (((T>NUM)AND (ST_CH='1'))OR (UPIN='1'))THEN
        CASE T IS
        WHEN 1  => UR(1)<='1';
        WHEN 2  => UR(2)<='1';
        WHEN 3  => UR(3)<='1';
        WHEN 4  => UR(4)<='1';
        WHEN 5  => UR(5)<='1';
        WHEN 6  => UR(6)<='1';
        WHEN 7  => UR(7)<='1';
        WHEN 8  => UR(8)<='1';
		WHEN 9  => UR(9)<='1';
        WHEN 10 => UR(10)<='1';
        WHEN 11 => UR(11)<='1';
        WHEN 12 => UR(12)<='1';
        WHEN 13 => UR(13)<='1';
        WHEN 14 => UR(14)<='1';
        WHEN 15 => UR(15)<='1';
        WHEN 16 => UR(16)<='1';
        WHEN OTHERS=>NULL;
        END CASE;
ELSIF (HAND='1')THEN 
        CASE NUM IS
        WHEN 1  => UR(1)<='0';
        WHEN 2  => UR(2)<='0';
        WHEN 3  => UR(3)<='0';
        WHEN 4  => UR(4)<='0';
        WHEN 5  => UR(5)<='0';
        WHEN 6  => UR(6)<='0';
        WHEN 7  => UR(7)<='0';
        WHEN 8  => UR(8)<='0';
        WHEN 9  => UR(9)<='0';
WHEN 10 => UR(10)<='0';
        WHEN 11 => UR(11)<='0';
        WHEN 12 => UR(12)<='0';
        WHEN 13 => UR(13)<='0';
        WHEN 14 => UR(14)<='0';
        WHEN 15 => UR(15)<='0';
        WHEN 16 => UR(16)<='0';
        WHEN OTHERS=>NULL;
        END CASE;
      END IF;
IF (((T<NUM)AND (ST_CH='1'))OR(DOWNIN='1')) THEN
        CASE T IS
        WHEN 1  => DR(1)<='1';
        WHEN 2  => DR(2)<='1';
        WHEN 3  => DR(3)<='1';
        WHEN 4  => DR(4)<='1';
        WHEN 5  => DR(5)<='1';
        WHEN 6  => DR(6)<='1';
        WHEN 7  => DR(7)<='1';
        WHEN 8  => DR(8)<='1';
        WHEN 9  => DR(9)<='1';
		WHEN 10 => DR(10)<='1';
        WHEN 11 => DR(11)<='1';
        WHEN 12 => DR(12)<='1';
        WHEN 13 => DR(13)<='1';
        WHEN 14 => DR(14)<='1';
        WHEN 15 => DR(15)<='1';
        WHEN 16 => DR(16)<='1';
        WHEN OTHERS=>NULL;
        END CASE;
      ELSIF (HAND='1') THEN 
        CASE NUM IS
		WHEN 1  => DR(1)<='0';
        WHEN 2  => DR(2)<='0';
        WHEN 3  => DR(3)<='0';
        WHEN 4  => DR(4)<='0';
        WHEN 5  => DR(5)<='0';
        WHEN 6  => DR(6)<='0';
        WHEN 7  => DR(7)<='0';
        WHEN 8  => DR(8)<='0';
        WHEN 9  => DR(9)<='0';
        WHEN 10 => DR(10)<='0';
		WHEN 11 => DR(11)<='0';
        WHEN 12 => DR(12)<='0';
        WHEN 13 => DR(13)<='0';
        WHEN 14 => DR(14)<='0';
        WHEN 15 => DR(15)<='0';
        WHEN 16 => DR(16)<='0';
        WHEN OTHERS=>NULL;
        END CASE;
      END IF;
ELSE 
      UR<="0000000000000000";
      DR<="0000000000000000";
   END IF;
 END PROCESS;
 
--电梯运行次态的控制进程
P3:PROCESS(UR,DR,LIFTOR,LADD,WAI_T,RUN_STOP)
BEGIN
  IF (RUN_STOP='1') THEN
     IF (WAI_T="110") THEN
        IF ((UR OR DR)="0000000000000000") THEN 
          LADD(1)<='0';  --初始状态
        ELSE
          CASE LIFTOR IS
WHEN "0000"=>IF ((UR(1)OR DR(1))>'0') THEN LADD(1)<='0';  --等待状态
                        ELSE LADD<="11"; 	 --上升状态
                        END IF;
             WHEN "0001"=>IF ((UR(2)OR DR(2))>'0') THEN LADD(1)<='0'; --等待状态
               ELSIF ((( LADD(0)='1')AND ((UR(16 DOWNTO 3)

OR DR(16 DOWNTO 3))>"00000000000000"))
                                 OR((UR(1)OR DR(1))='0')) THEN 
                                 LADD <="11"; 	--上升状态
                         ELSE LADD<="10";  	--下降状态
                         END IF;
WHEN "0010"=>IF ((UR(3) OR DR(3))>'0') THEN LADD(1)<='0';
                         ELSIF ((( LADD(0)='1')AND ((UR(16 DOWNTO 4)
                                 OR DR(16 DOWNTO 4))>"0000000000000"))
                                 OR((UR(2 DOWNTO 1)
                                 OR DR(2 DOWNTO 1))="00")) THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;
WHEN "0011"=>IF ((UR(4) OR DR(4))>'0') THEN LADD(1)<='0';
                         ELSIF (((LADD(0)='1')AND ((UR(16 DOWNTO 5)
                              OR DR(16 DOWNTO 5))>"000000000000"))
                              OR((UR(3 DOWNTO 1)
                              OR DR(3 DOWNTO 1))="000")) THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;

WHEN "0100"=>IF ((UR(5) OR DR(5))>'0') THEN LADD(1)<='0';
                         ELSIF (((LADD(0)='1')AND ((UR(16 DOWNTO 6)
                              OR DR(16 DOWNTO 6))>"00000000000"))
                              OR((UR(4 DOWNTO 1)
                              OR DR(4 DOWNTO 1))="0000")) THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;
WHEN "0101"=>IF ((UR(6) OR DR(6))>'0') THEN LADD(1)<='0';
                         ELSIF (((LADD(0)='1')AND ((UR(16 DOWNTO 7)
                              OR DR(16 DOWNTO 7))>"0000000000" ))
                              OR((UR(5 DOWNTO 1)
                              OR DR(5 DOWNTO 1))="00000")) THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;
WHEN "0110"=>IF ((UR(7) OR DR(7))>'0') THEN LADD(1)<='0';
                         ELSIF (((LADD(0)='1')AND ((UR(16 DOWNTO 8)
                                 OR DR(16 DOWNTO 8))>"000000000"))
                                 OR((UR(6 DOWNTO 1)
                                 OR DR(6 DOWNTO 1))="000000")) 
 THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;

WHEN "0111"=>IF ((UR(8) OR DR(8))>'0') THEN LADD(1)<='0';
                         ELSIF (((LADD(0)='1')AND ((UR(16 DOWNTO 9)
                                 OR DR(16 DOWNTO 9))>"00000000" ))
                                 OR((UR(7 DOWNTO 1)
                                 OR DR(7 DOWNTO 1))="0000000"))
    THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;
WHEN "1000"=>IF ((UR(9) OR DR(9))>'0') THEN LADD(1)<='0';
                      ELSIF ((( LADD(0)='1')AND ((UR(16 DOWNTO 10)
                                 OR DR(16 DOWNTO 10))>"0000000" ))
                                 OR((UR(8 DOWNTO 1)
                                 OR DR(8 DOWNTO 1))="00000000"))
THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;
WHEN "1001"=>IF ((UR(10) OR DR(10))>'0') THEN LADD(1)<='0';
                    ELSIF ((( LADD(0)='1')AND ((UR(16 DOWNTO 11)
                                 OR DR(16 DOWNTO 11))>"000000" ))
                                 OR((UR(9 DOWNTO 1)
                                 OR DR(9 DOWNTO 1))="000000000"))
    THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;
WHEN "1010"=>IF ((UR(11) OR DR(11))>'0') THEN LADD(1)<='0';
                     ELSIF (((LADD(0)='1')AND ((UR(16 DOWNTO 12)
                                 OR DR(16 DOWNTO 12)) >"00000"))
                                 OR((UR(10 DOWNTO 1)
                                 OR DR(10 DOWNTO 1))="0000000000"))
   THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;
WHEN "1011"=>IF ((UR(12) OR DR(12))>'0') THEN LADD(1)<='0';
                         ELSIF ((( LADD(0)='1')AND ((UR(16 DOWNTO 13)
                                 OR DR(16 DOWNTO 13))>"0000" ))
                                 OR((UR(11 DOWNTO 1)
                                 OR DR(11 DOWNTO 1))="00000000000"))
    THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;
WHEN "1100"=>IF ((UR(13) OR DR(13))>'0') THEN LADD(1)<='0';
                         ELSIF ((( LADD(0)='1')AND ((UR(16 DOWNTO 14)
                                 OR DR(16 DOWNTO 14))>"000" ))
                                 OR((UR(12 DOWNTO 1)
                                 OR DR(12 DOWNTO 1))="000000000000"))
    THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;
WHEN "1101"=>IF ((UR(14) OR DR(14))>'0') THEN LADD(1)<='0';
                         ELSIF ((( LADD(0)='1')AND ((UR(16 DOWNTO 15)
                                 OR DR(16 DOWNTO 15))>"00" ))
                                 OR((UR(13 DOWNTO 1)
                                 OR DR(13 DOWNTO 1))="0000000000000"))
    THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;

WHEN "1110"=>IF ((UR(15)OR DR(15))>'0') THEN LADD(1)<='0';
                         ELSIF ((( LADD(0)='1')AND ((UR(16)OR DR(16))>'0'))
                                 OR ((UR(14 DOWNTO 1)
                                 OR DR(14 DOWNTO 1))="00000000000000"))
  THEN LADD<="11";
                         ELSE LADD<="10";
                         END IF;
             WHEN "1111"=>IF ((UR(16) OR DR(16))>'0') THEN LADD(1)<='0';

                         ELSE LADD<="10";
                         END IF;
             WHEN OTHERS=>NULL;
           END CASE;
         END IF;
       END IF;
        ELSE LADD<="00";
     END IF;
 END PROCESS;
--电梯运行楼层计数及提前/延迟关门控制进程
P4:PROCESS(WAI_T,LADD,CLOSEX,DELAYX,DIVID)
 BEGIN
    IF (DIVID'EVENT AND DIVID='1') THEN
       IF (WAI_T="000" OR CLOSEX='1') THEN WAI_T<="110";
       ELSE
          IF (DELAYX='0')THEN WAI_T<=WAI_T-1;
          ELSE WAI_T<="010";
          END IF;
IF (LADD="11") THEN LIFTOR<=LIFTOR+1;
          ELSIF (LADD="10") THEN LIFTOR<=LIFTOR-1;
          END IF;
        END IF;
     END IF;
 END PROCESS;
END ARCHITECTURE ART;

