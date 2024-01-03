`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 16:32:43
// Design Name: 
// Module Name: dmem
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


module dmem(
input clk,
input we1,
input [31:0]addr1,
input [31:0]datain1,
input we2,
input [31:0]addr2,
input [31:0]datain2,
output [31:0]dataout1,
output [31:0]dataout2
    );
reg [31:0]RAM[0:255];
/*integer i;
initial
i=0;
if(i<64) 
begin
RAM[i]=32'h0;
i=i+1;
end
*/
assign dataout1=RAM[addr1];
assign dataout2=RAM[addr2];
always@(posedge clk)
begin
    if(we1) RAM[addr1]=datain1;
    if(we2) RAM[addr2]=datain2;
end
endmodule
