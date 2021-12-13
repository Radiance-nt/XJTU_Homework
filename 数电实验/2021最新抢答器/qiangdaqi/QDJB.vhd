--QDJB.VHD
library ieee;
use ieee.std_logic_1164.all;
entity QDJB is
 port(CLR: in std_logic;
	A,B,C,D: in std_logic;
	A1,B1,C1,D1: out std_logic;
	states: out std_logic_vector(3 downto 0));
end entity QDJB;
architecture art of QDJB is
 constant W1: std_logic_vector:="0001";
 constant W2: std_logic_vector:="0010";
 constant W3: std_logic_vector:="0100";
 constant W4: std_logic_vector:="1000";
 begin
 process(CLR,A,B,C,D) is
 begin
 if CLR='1' then states<="0000";A1<='0';B1<='0';C1<='0';D1<='0';
	elsif (A='1' and B='0' and C='0' and D='0')then
	 A1<='1';B1<='0';C1<='0';D1<='0';states<=W1;
	elsif (A='0' and B='1' and C='0' and D='0')then
	 A1<='0';B1<='1';C1<='0';D1<='0';states<=W2;
	elsif (A='0' and B='0' and C='1' and D='0')then
	 A1<='0';B1<='0';C1<='1';D1<='0';states<=W3;
	elsif (A='0' and B='0' and C='0' and D='1')then
	 A1<='0';B1<='0';C1<='0';D1<='1';states<=W4;
	end if;
 end process;
end architecture art;

	