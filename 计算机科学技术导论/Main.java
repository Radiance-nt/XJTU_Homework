
/*2、	统计这两个文档中有多少字符相同，有多少个字符不同
        统计出前10个高频字或词；
*/
package COUNT;

import org.apache.poi.hwpf.extractor.WordExtractor;

import java.io.*;
import java.util.*;
import java.util.Map.Entry;


public class Main {

    static Map<String, Integer> InputFile_Sort(String filename) {
        try {
            List<String> list = new ArrayList<String>();
            File f = new File(filename);
            if (filename.endsWith(".doc")) {
                String s = "";
                FileInputStream is = new FileInputStream(f);
                WordExtractor ex = new WordExtractor(is);
                s = ex.getText();
                ex.close();
                s=s.toLowerCase();
                String[] strings = s.split("[^a-zA-Z]");
                for (String word : strings) {
                    if (word.length() != 0) {
                        list.add(word);
                    }
                }
            }
            Map<String, Integer> counter = new TreeMap<String, Integer>();
            for (String li : list) {
                if (counter.get(li) != null) {
                    counter.put(li, counter.get(li) + 1);
                } else {
                    counter.put(li, 1);
                }
            }
            // 按值进行排序
            return counter;
        } catch (IOException exception) {
            // TODO Auto-generated catch block
            exception.printStackTrace();
            return null;
        }
    }

    public static ArrayList<Map.Entry<String, Integer>> Sort_(Map<String, Integer> map) {
        ArrayList<Map.Entry<String, Integer>> l = new ArrayList<Map.Entry<String, Integer>>(map.entrySet());
        Collections.sort(l, new Comparator<Map.Entry<String, Integer>>() {
            @Override
            public int compare(Entry<String, Integer> entry1,
                               Entry<String, Integer> entry2) {
                return entry2.getValue() - entry1.getValue();
            }
        });
        return l;
    }

    public static void Out_put(Map<String, Integer> map1, Map<String, Integer> map2) {

        File f = new File(".\\res.txt");
        BufferedWriter writer;
        ArrayList<Map.Entry<String, Integer>> list1 = Sort_(map1);
        ArrayList<Map.Entry<String, Integer>> list2 = Sort_(map2);

        try {
            writer = new BufferedWriter(new FileWriter(f));
            writer.write("第一篇：");
            System.out.println("第一篇：");
            writer.newLine();
            for (int i = 0; i < 10; i++) {
                writer.write(list1.get(i).getKey() + ":" + list1.get(i).getValue());
                System.out.println(list1.get(i).getKey() + ":" + list1.get(i).getValue());
                writer.newLine();
            }
            writer.newLine();
            writer.flush();
            writer.newLine();
            System.out.println();
            writer.write("第二篇：");
            System.out.println("第二篇：");
            writer.newLine();
            for (int i = 0; i < 10; i++) {
                writer.write(list2.get(i).getKey() + ":" + list2.get(i).getValue());
                System.out.println(list2.get(i).getKey() + ":" + list2.get(i).getValue());
                writer.newLine();
            }
            writer.newLine();
            System.out.println();
            writer.flush();

            int sum_un = 0, sum_eq = 0;
            for (String key : map1.keySet()) {
                if (map2.get(key) != null) {
                    sum_eq += 1;
                }
            }
            sum_un=map1.size()+map2.size()-2*sum_eq;
            writer.newLine();
            System.out.println();
            writer.write("相同单词数量:" + sum_eq);
            System.out.println("相同单词数量:" + sum_eq);
            writer.newLine();
            writer.write("不同单词数量:" + sum_un);
            System.out.println("不同单词数量:" + sum_un);
            writer.newLine();
            writer.close();

        } catch (IOException exception) {
            // TODO Auto-generated catch block
            exception.printStackTrace();
        }
        System.out.println("################");
        System.out.println("统计完毕！");
    }

    public static void main(String[] args) throws IOException {
        System.out.println("****************比较文档相似度-功能预览***************");
        System.out.println("* 依次输入两个doc文件");
        System.out.println("* 统计出前10个高频单词");
        System.out.println("* 统计这两个文档中有多少单词相同");
        System.out.println("**************************************************");

        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入文件名1：");
        String filename = scanner.nextLine();
        Map<String, Integer> wordsCount1 = InputFile_Sort(filename);
        System.out.println("请输入文件名2：");
        filename = scanner.nextLine();
        Map<String, Integer> wordsCount2 = InputFile_Sort(filename);
        Out_put(wordsCount1, wordsCount2);

    }
}
