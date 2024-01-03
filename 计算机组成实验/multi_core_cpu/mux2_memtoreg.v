`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 16:01:44
// Design Name: 
// Module Name: mux2_memtoreg
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


module mux2_memtoreg(
input memtoreg,
input [31:0]memdata,
input [31:0]aludata,
output [31:0]regin
    );
assign regin=(memtoreg!=0)?memdata:aludata;
endmodule
