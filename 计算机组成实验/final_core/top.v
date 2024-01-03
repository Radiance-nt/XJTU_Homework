`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/28 19:21:16
// Design Name: 
// Module Name: top
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


module top(
input clk,
input reset,
output [31:0]instruc,
output [31:0]data_addr,
output [31:0]write_data,
output [31:0]pc_data,



output [31:0]regin_data,reg_rd1,
output [4:0]regra1,regra2,regwa3,

output [31:0]instruc1,
output [31:0]data_addr1,
output [31:0]write_data1,
output [31:0]pc_data1,



output [31:0]regin_data1,reg_rd11,
output [4:0]regra11,regra21,regwa31,

output [31:0]dmem_dataout,
output [31:0]dmem_dataout1,
output we,
output we1
//output [31:0]pc_next_cpu,pc_next_cpu1
    );
wire [31:0]pc_addr,d_addr,w_data;
wire [31:0]wd,da,instr,readdata;
wire memwrite,mem_toreg;

wire [31:0]pc_addr1,d_addr1,w_data1;
wire [31:0]wd1,da1,instr1,readdata1;
wire [31:0]imem_oaddr,imem_oaddr1;
wire memwrite1,mem_toreg1;

assign data_addr=d_addr;
assign write_data=w_data;
assign we=memwrite;
assign instruc=instr;
assign pc_data=pc_addr;
assign dmem_dataout=readdata;

assign data_addr1=d_addr1;
assign write_data1=w_data1;
assign we1=memwrite1;
assign instruc1=instr1;
assign pc_data1=pc_addr1;
assign dmem_dataout1=readdata1;

//cpu cpu_32(clk,instr1, reset,32'h00000000,readdata,imem_oaddr1,pc_addr,pc_after_j,d_addr,w_data,regin_data,reg_rd1,regra1,regra2,regwa3,memwrite);

cpu cpu_32(clk,instr, reset,32'h00000000,readdata,pc_addr,d_addr,w_data,regin_data,reg_rd1,regra1,regra2,regwa3,memwrite);
cpu cpu_32_1(clk,instr1, reset,32'h00000012,readdata1,pc_addr1,d_addr1,w_data1,regin_data1,reg_rd11,regra11,regra21,regwa31,memwrite1);

dmem dmem_32(clk,memwrite,d_addr,w_data,memwrite1,d_addr1,w_data1,readdata,readdata1);

imem imem_32(pc_addr,pc_addr1,instr,instr1);

endmodule
