`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 16:16:27
// Design Name: 
// Module Name: mux2_branch
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


module mux2_branch(
input branch,
input [31:0]jaddr,
input [31:0]addr1,
output [31:0]nextaddr
    );
    assign nextaddr=(branch!=0)?jaddr:addr1;
endmodule
