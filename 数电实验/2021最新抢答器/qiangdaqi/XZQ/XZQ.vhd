--XZQ.VHD
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity XZQ is
port(CLR,A,B,C,D:in std_logic;
	AA:in std_logic_vector(3 downto 0);
	BB:in std_logic_vector(3 downto 0);
	CC:in std_logic_vector(3 downto 0);
	DD:in std_logic_vector(3 downto 0);
	OUTW:out std_logic_vector(3 downto 0));	
end entity XZQ;
architecture art of XZQ is 
signal temp: std_logic_vector(3 downto 0);
 begin
process(A,B,C,D,CLR) is
	begin
	if CLR='1' then
	 temp<="0000";
	elsif A='1' then
	 temp<=AA;
	elsif B='1' then
	 temp<=BB;
	elsif C='1' then
	 temp<=CC;
	elsif D='1' then
	 temp<=DD;
	end if;
	OUTW<=temp;
 end process;
END ARCHITECTURE art;