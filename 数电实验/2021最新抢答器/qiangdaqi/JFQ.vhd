--JFQ.VHD
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity JFQ is
 port(rst: in std_logic;
	add: in std_logic;
	chos:in std_logic_vector(3 downto 0);
	AA1,BB1: out std_logic_vector(3 downto 0);
 	CC1,DD1: out std_logic_vector(3 downto 0));
end entity JFQ;
architecture art of JFQ is 
 begin
 process(add,rst,chos) is 
	variable points_A1:std_logic_vector(3 downto 0);
	variable points_B1:std_logic_vector(3 downto 0);
	variable points_C1:std_logic_vector(3 downto 0);
	variable points_D1:std_logic_vector(3 downto 0);

 begin
	
	if (rst='1') then
	  points_A1:="0000";
	  points_B1:="0000";
	  points_C1:="0000";
	  points_D1:="0000";
	elsif (add'event and  add='1') then
	 if chos="0001" then
	  if points_A1="1001" then
		 points_A1:="0000";
	  else 
		points_A1:=points_A1+'1';
	  end if;
	  elsif chos="0010" then
	  if points_B1="1001" then
		points_B1:="0000";
		else
		points_B1:=points_B1+'1';
	  end if;
	  elsif chos="0100" then
	  if points_C1="1001" then
		points_C1:="0000";
	  else 
		points_C1:=points_C1+'1';
	  end if;
	  elsif chos="1000" then
	  if points_D1="1001" then
		points_D1:="0000";
	  else 
		points_D1:=points_D1+'1';
	  end if;
	 end if;
	end if;
	AA1<=points_A1;
	BB1<=points_B1;
	CC1<=points_C1;
	DD1<=points_D1;
 end process;
end architecture art;
	 
	