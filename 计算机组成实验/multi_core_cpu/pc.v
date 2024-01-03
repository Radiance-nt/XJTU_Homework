`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 16:10:01
// Design Name: 
// Module Name: pc
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


module pc(
input clk,
input [31:0]paddr,
input reset,
input [31:0]reset_data,
output reg [31:0]naddr
    );
always@(posedge clk,posedge reset)
    begin
        if(reset==0)
 //           naddr<=(paddr>>2);
            naddr<=(paddr);
        else naddr<=reset_data;
   end
endmodule
