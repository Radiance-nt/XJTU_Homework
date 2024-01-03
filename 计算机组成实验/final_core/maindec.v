`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/02 15:27:33
// Design Name: 
// Module Name: maindec
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


module maindec(input [5:0] op,
output regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump,
output [1:0] aluop);
reg [8:0]controls;
assign {regwrite,regdst,alusrc,branch,memwrite,
memtoreg,jump,aluop}=controls;
//�Ĵ���дʹ�ܣ�Ŀ��Ĵ�����ţ���·ѡ�񣩣������ԼĴ���or����������ӦBEQָ�alu����zero��־λΪ1��Ч����
//д�ڴ�ʹ���źţ����ݴ��ڴ滹��alu������ת��aluop
always @(*)
    begin
    case(op)
    6'b000000: controls <=9'b110000010;//Rtype
    6'b100011: controls <=9'b101001000;//LW
    6'b101011: controls <=9'b001010000;//SW
    6'b000100: controls <=9'b000100001;//BEQ
    6'b001000: controls <=9'b101000000;//Addi
    6'b000010: controls <=9'b000000100;//J
    default: controls <=9'bxxxxxxxxx;
    endcase
    end
endmodule
