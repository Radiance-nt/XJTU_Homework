`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/02 15:48:10
// Design Name: 
// Module Name: alu_32
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


module alu_32(

ain,bin,cout,choose,zero
    );
    input [31:0] ain,bin;
    input [2:0]choose;
    output reg [31:0] cout;
    output reg zero;
    always@(*)
    begin
            case(choose)
            3'b010:
            begin
                 cout=ain+bin;
            end
            3'b110:
            begin
                cout=ain-bin;
            end
            3'b000:cout=ain&bin;
            3'b001:cout=ain|bin;
            3'b100:
            begin
            if(ain<bin)cout=32'b1;
            else cout=32'h00000000;
            end
            endcase
     if(cout!=0) zero =0;
     else zero=1;
 end
endmodule
