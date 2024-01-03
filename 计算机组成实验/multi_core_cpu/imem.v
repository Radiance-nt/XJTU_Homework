`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 16:32:25
// Design Name: 
// Module Name: imem
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module imem(

input [31:0]addr1,
input [31:0]addr2,
input reset,
output reg[31:0]rd1,
output reg[31:0]o_addr1,
output reg[31:0]rd2,
output reg[31:0]o_addr2
    );
reg [31:0]RAM[0:63];
initial
begin 
    $readmemh("D:/instruction_18.txt",RAM);
end

 always@(*)
 begin
       if(reset==0)
       begin
       o_addr1<=addr1;
       o_addr2<=addr2;
       rd1<=RAM[addr1];
       rd2<=RAM[addr2];
       end
       else 
       begin
       o_addr1<=32'h00000001;
       o_addr2<=32'h00000000;
       rd1<=RAM[32'h00000001];
       rd2<=RAM[32'h00000000];
       
       end
  end
endmodule
