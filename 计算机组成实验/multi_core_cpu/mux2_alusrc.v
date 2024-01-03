`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 15:52:13
// Design Name: 
// Module Name: mux2_alusrc
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


module mux2_alusrc(
input alusrc,
input [31:0]immedi,
input [31:0]regdata,
output [31:0]aludatain
    );
assign aludatain=(alusrc!=0)?immedi:regdata;
endmodule
