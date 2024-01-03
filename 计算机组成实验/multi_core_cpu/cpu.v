`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/27 17:22:52
// Design Name: 
// Module Name: cpu
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


module cpu(
input clk,
input [31:0] instr,
input reset,

input [31:0]reset_data,

input [31:0]dmemdata,

input [31:0]pc_cpuin,

output [31:0]pc_data,
output [31:0]pc_after_j,
//output [31:0]pc_next_cpu,
output [31:0]data_addr,
output [31:0]write_data,
output [31:0]regin_data,reg_rd1,
output [4:0]regra1,regra2,regwa3,
output we
);
wire regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump;
wire zero;
wire [5:0]op_code,funct;
wire [27:0]in_join;
assign in_join=instr[25:0]<<2;
assign op_code=instr[31:26];
assign funct=instr[5:0];

wire [1:0]aluop;
wire [2:0]alucontrol;
wire [4:0]ra1,ra2,wa3;
wire [31:0]wd3,rd1,rd2,alu_out;
assign ra1=instr[25:21];
assign ra2=instr[20:16];
assign regra1=ra1;
assign regra2=ra2;
assign regwa3=wa3;
//assign mem_toreg=memtoreg;

assign regin_data=wd3;
wire [31:0]im32,alu_in;
wire [31:0]pc_addr,pc_nojump,pc_jumpbeq,pc_jump,pc_afterb,pc_afterj,pc1;
assign pc_data=pc_addr;

assign pc_after_j=pc_afterj;
//assign pc_next_cpu=pc_afterj;
assign we=memwrite;
assign data_addr=alu_out;
assign write_data=rd2;
assign reg_rd1=rd1;
maindec Maindec(op_code,regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump,aluop);

mux2_regdst mux2r(regdst,instr[15:11],instr[20:16],wa3);

ext16 imto32(instr[15:0],im32);

aludec aludecoder(funct,aluop,alucontrol);

Register regfile(clk,regwrite,ra1,ra2,wa3,wd3,rd1,rd2);

mux2_alusrc mux2a(alusrc,im32,rd2,alu_in);

alu_32 alu(rd1,alu_in,alu_out,alucontrol,zero);

pc pcreg(clk,pc_afterj,reset,reset_data,pc_addr);

//adder pcadd1(pc_addr,32'h4,pc_nojump);
adder pcadd1(pc_cpuin,32'h1,pc_nojump);

adder pcadd2(pc_nojump,im32,pc_jumpbeq);
//有条件跳转送入alu，再判断相减是否为零
//beq通过指令译码器的最后两位aluop控制，不需要额外的


mux2_branch mux2b(zero&branch,pc_jumpbeq,pc_nojump,pc_afterb);


mux2_memtoreg mux2m(memtoreg,dmemdata,alu_out,wd3);



//jump_addr jumpaddr(pc_addr[31:28],in_join,pc_jump);
ext26 ext_26(instr[25:0],pc1);


//mux2_jump mux2j(jump,pc_jump,pc_afterb,pc_afterj);
mux2_jump mux2j(jump,pc1,pc_afterb,pc_afterj);






endmodule
