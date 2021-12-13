--JSQ.VHD
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity JSQ is
 port(CLR,LDN,EN,CLK:in std_logic;
	TA:in std_logic;
	QA:out std_logic_vector(3 downto 0));
end entity JSQ;
architecture art of JSQ is 
 signal DA: std_logic_vector(3 downto 0);
 begin
 process(TA,CLR) is
	begin
	if CLR='1' then
	 DA<="0000";
	else
	if TA='1' then
	 DA<="0101";
	end if;
	end if;
 end process;
 process(CLK) is
	variable TMPA:std_logic_vector(3 downto 0);
 begin
	if CLR='1' then TMPA:="0000";
	elsif CLK'event and CLK='1' then
	 if LDN='1' then TMPA:=DA;
	 elsif EN='1' then 
	  if TMPA="0000" then
	   TMPA:="1001";
	  else TMPA:= TMPA-1;
	 end if;
	   end if;
	 end if;
	QA<=TMPA;
 end process;
end architecture art;
	
	
	 
	
	