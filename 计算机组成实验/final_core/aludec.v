`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/02 15:37:49
// Design Name: 
// Module Name: aludec
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


module aludec(input [5:0] funct,
input [1:0] aluop,
output reg [2:0] alucontrol);
always @ (*)
    case (aluop)
        2'b00: alucontrol <=3'b010;//add
        2'b01: alucontrol <=3'b110;//sub
        default:case(funct)
            6'b100000:alucontrol <=3'b010;//add
            6'b100010:alucontrol <=3'b110;//sub
            6'b100100:alucontrol <=3'b000;//and
            6'b100101:alucontrol <=3'b001;//or
            6'b101010:alucontrol <=3'b100;
        endcase
    endcase
endmodule




