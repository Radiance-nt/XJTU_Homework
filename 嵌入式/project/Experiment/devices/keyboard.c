#include "keyboard.h"


void keyboard_init(void){
    register_intr_handler(INTR_KEYBD, keyboard_intr_handler, "Keyboard Interrupt");
}

#define KEY_BUF_PROT    0x60            // 键盘寄存器端口号是0x60


// 定义控制字符
#define esc             '\033'
#define backsapce       '\b'
#define tab             '\t'
#define enter           '\r'
#define delete          '\177'

// 定义控制字符对应的按键，即控制按键
#define invisible_char  0
#define ctrl_l_char     invisible_char
#define ctrl_r_char     invisible_char
#define shift_l_char    invisible_char
#define shift_r_char    invisible_char
#define alt_l_char      invisible_char
#define alt_r_char      invisible_char
#define capslock_char   invisible_char

// 定义控制字符对应按键的通码和断码
#define shift_l_make    0x2a
#define shift_r_make    0x36
#define alt_l_make      0x38
#define alt_r_make      0xE038
#define alt_r_break     0xE0B8
#define ctrl_l_make     0x1D
#define ctrl_r_make     0xE01D
#define ctrl_r_break    0xE09D
#define casplock_make   0x3A


// 标记每个控制按键的状态
static Bool ctrl_status, shift_status, alt_status, capslock_status, ext_scancode;

// 按键对应的字符与按下Shift后的按键对应的字符
static char keymap[][2] = {
    {0,     0},                         // 0x00
    {esc,   esc},                       // 0x01
    {'1',   '!'},                       // 0x02
    {'2',   '@'},                       // 0x03
    {'3',   '#'},                       // 0x04
    {'4',   '$'},                       // 0x05
    {'5',   '%'},                       // 0x06
    {'6',   '^'},                       // 0x07
    {'7',   '&'},                       // 0x08
    {'8',   '*'},                       // 0x09
    {'9',   '('},                       // 0x0A
    {'0',   ')'},                       // 0x0B
    {'-',   '_'},                       // 0x0C
    {'=',   '+'},                       // 0x0D
    {backsapce,     backsapce},         // 0x0E
    {tab,   tab},                       // 0x0F
    {'q',   'Q'},                       // 0x10
    {'w',   'W'},                       // 0x11
    {'e',   'E'},                       // 0x12
    {'r',   'R'},                       // 0x13
    {'t',   'T'},                       // 0x14
    {'y',   'Y'},                       // 0x15
    {'u',   'U'},                       // 0x16
    {'i',   'I'},                       // 0x17
    {'o',   'O'},                       // 0x18
    {'p',   'P'},                       // 0x19
    {'[',   '{'},                       // 0x1A
    {']',   '}'},                       // 0x1B
    {enter, enter},                     // 0x1C
    {ctrl_l_char, ctrl_l_char},         // 0x1D
    {'a',   'A'},                       // 0x1E
    {'s',   'S'},                       // 0x1F
    {'d',   'D'},                       // 0x20
    {'f',   'F'},                       // 0x21
    {'g',   'G'},                       // 0x22
    {'h',   'H'},                       // 0x23
    {'j',   'J'},                       // 0x24
    {'k',   'K'},                       // 0x25
    {'l',   'L'},                       // 0x26
    {';',   ':'},                       // 0x27
    {'\'',  '"'},                       // 0x28
    {'`',   '~'},                       // 0x29
    {shift_l_char, shift_l_char},       // 0x2A
    {'\\',  '|'},                       // 0x2B
    {'z',   'Z'},                       // 0x2C
    {'x',   'X'},                       // 0x2D
    {'c',   'C'},                       // 0x2E
    {'v',   'V'},                       // 0x2F
    {'b',   'B'},                       // 0x30
    {'n',   'N'},                       // 0x31
    {'m',   'M'},                       // 0x32
    {',',   '<'},                       // 0x33
    {'.',   '>'},                       // 0x34
    {'/',   '?'},                       // 0x35
    {shift_r_char, shift_r_char},       // 0x36
    {'*',   '*'},                       // 0x37
    {alt_l_char, alt_l_char},           // 0x38
    {' ',   ' '},                       // 0x39
    {capslock_char, capslock_char},     // 0x3A
};

int32_t keyboard_intr_handler(trapframe_t *tf_ptr){
    Bool ctrl_down_last = ctrl_status;
    Bool shift_down_last = shift_status;
    Bool capslock_last = capslock_status;

    Bool break_code;
    uint16_t scancode = inb(KEY_BUF_PROT);          // 读取键盘扫描码

    // 若以E0开头，表示该按键为扩展按键，需要读取更多的扫码码
    if (scancode == 0xE0) {
        ext_scancode = True;
        return;
    }
    // 若上个按键是0xE0，则合并得到新的扫描码
    if (ext_scancode){
        scancode = 0xE000 | inb(KEY_BUF_PROT);
        ext_scancode = False;                       // 重置标记
    }

    // 检测是否是断码
    break_code = ((scancode & 0x0080) != 0);
    if (break_code){
        // 将断码转换为通码 & 0x1111_1111_0111_1111
        uint16_t make_code = (scancode &= 0xFF7F);

        // 若松开的是ctrl、shift、alt，则复位全局状态
        // 这个主要是为了对ctrl+a、shift+b、alt+c这种进行配合
        // 一般按下组合键的顺序是：先按控制键，然后按另外一个键
        // 所以才会有ctrl_status、alt_status、shift_status这三个全局变量来保存上次按键的状态
        // 所以这里才需要进行复位处理
        if (make_code == ctrl_l_make || make_code == ctrl_r_make)
            ctrl_status = False;
        else if (make_code == alt_l_make || make_code == alt_r_make)
            alt_status = False;
        else if (make_code == shift_l_make || make_code == shift_r_make)
            shift_status = False;
        
        // 其他按键的断码直接忽略
        return;
    }


    // 除了通码就是断码，这里先进行一下范围检查
    // 目前通码只有数组中定义的通码、alt和ctrl
    if (!((0x00 < scancode && scancode < 0x3B) || (scancode == alt_r_make) || (scancode == ctrl_r_make))){
        put_str("unkonw key, scancode = 0x");
        put_int(scancode);
        put_char('\n');
        return;
    }

    // 按下了通码，但是这个时候还需要判断到底使用二维数组中的哪一个
    // 例如如果同时按下shift，那么就要用第二个，或者之前按下了capslock，那么也用第二个
    // 所以在这里就是判断使用二维数组中的哪一个，本质上shift和capslock都是使用第二个
    Bool last = False;

    // 先处理非字母按键，包括数字和符号，因为之和shift有关
    if ( (scancode < 0x0E) || (scancode == 0x29) || (scancode == 0x1A) || (scancode == 0x1B) || (scancode == 0x2B) || 
        (scancode == 0x27) || (scancode == 0x28) || (scancode == 0x33) || (scancode == 0x34) || (scancode == 0x35)) {
        if (shift_down_last)
            last = True;
    } else {
        // 然后处理字母按键，还要考虑capslock
        if (shift_down_last && capslock_last)
            last = False;
        else if (shift_down_last || capslock_last)
            last = True;
    }

    // 扫描码高字节清0，避免扩展扫码码带来的问题
    uint8_t index = (scancode &= 0x00FF);
    char cur_char = keymap[index][last];

    // 处理快捷键
    if ((ctrl_down_last && cur_char == 'l') || (ctrl_down_last && cur_char == 'u'))
        cur_char -= 'a';

    // 目前只处理非控制字符
    if (cur_char){
        kb_buf[(kb_buf_pos = (kb_buf_pos + 1) % KBBUF_MAX)] = cur_char;
        return;
    }

    // 最后需要更新一下是否按下了控制字符
    if (scancode == ctrl_l_make || scancode == ctrl_r_make)
        ctrl_status = True;
    else if (scancode == alt_l_make || scancode == alt_r_make)
        alt_status = True;
    else if (scancode == shift_l_make || scancode == shift_r_make)
        shift_status = True;
    else if (scancode == casplock_make)
        capslock_status = !capslock_status;      // 再次按下capslock，取反即可
}