`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 15:39:24
// Design Name: 
// Module Name: mux2_regdst
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


module mux2_regdst(
input regdst,
input [4:0]R_rd,
input [4:0]I_rt,
output [4:0]dst
    );
assign dst=(regdst!=0)?R_rd:I_rt; 
endmodule
