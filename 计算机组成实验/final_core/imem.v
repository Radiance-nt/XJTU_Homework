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

input [31:0]addr,
input [31:0]addr1,
output [31:0]rd,
output [31:0]rd1
    );
reg [31:0]RAM[0:63];
initial
begin 
    $readmemh("D:/multi_instruction_18.txt",RAM);
end
assign rd=RAM[addr];
assign rd1=RAM[addr1];
endmodule
