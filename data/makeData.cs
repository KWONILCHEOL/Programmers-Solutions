using System;
using System.IO;
using System.Windows.Forms;
using Microsoft.WindowsAPICodePack.Dialogs;
namespace makeJson
{
    public partial class Baekjoon : Form
    {
        public string[] dirs;
        public string[] id;
        public string[] level;
        public string[] title;
        public string[] category;
        public string[] link;
        public string[] language;

        public Baekjoon()
        {
            InitializeComponent();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            makeMainData();
        }
        private void makeMainData()
        {
            CommonOpenFileDialog ofd = new CommonOpenFileDialog();
            ofd.IsFolderPicker = true;
            if (ofd.ShowDialog() != CommonFileDialogResult.Ok)
                return;
            textBox1.Text = ofd.FileName;
            dirs = Directory.GetDirectories(textBox1.Text);
            int size = dirs.Length;
            id = new string[size];
            level = new string[size];
            title = new string[size];
            category = new string[size];
            link = new string[size];
            language = new string[size];
            string data = "";
            for (int i = 0; i < size; i++)
            {
                string filename = Path.GetFileName(dirs[i]);
                id[i] = filename.Split(' ')[0].Substring(4);
                level[i] = filename.Substring(1, 2);
                title[i] = filename.Substring(id[i].Length + level[i].Length + 3);
                category[i] = "연습문제";

                string temp = filename.Replace("[", @"%5B").Replace("]", @"%5D").Replace(" ", @"%20");
                link[i] = string.Format("[문제](https://www.acmicpc.net/problem/{0}) / [풀이](/solutions/{1}/)", id[i], temp);
                string[] files = Directory.GetFiles(dirs[i]);
                foreach (string file in files)
                {
                    string ext = Path.GetExtension(file).Substring(1);
                    if (ext == "md")
                        continue;

                    if (ext == "py")
                        language[i] += string.Format("[![python3](/assets/python3.svg)](/solutions/{1}/submit.{0}) ", ext, temp);
                    else
                        language[i] += string.Format("[![{0}](/assets/{0}.svg)](/solutions/{1}/submit.{0}) ", ext, temp);
                }
                makeSubMD(i);
                data += string.Format("| {0} | {1} | {2} | {3} | {4} | {5} |\n", id[i], level[i], title[i], category[i], link[i], language[i]);
            }
            File.WriteAllText(textBox1.Text + "\\data.txt", data);
        }
        private void makeSubMD(int i)
        {
            string md = "";
            md += "| ID | 난이도 | 제목 | 분류 | 링크 | 언어 |\n";
            md += "| -- | ---- | :-- | :-- | --- | --- |\n";
            md += string.Format("| {0} | {1} | {2} | {3} | {4} | {5} |\n\n", id[i], level[i], title[i], category[i], link[i].Split(')')[0] + ")", language[i]);

            md += "| 언어 | short | solution | submit |\n";
            md += "| --- | ----- | -------- | ------ |\n";
            string[] files = Directory.GetFiles(dirs[i]);
            foreach (string file in files)
            {
                string filename = Path.GetFileNameWithoutExtension(file);
                string ext = Path.GetExtension(file).Substring(1);
                if (ext == "md")
                    continue;

                if (filename == "short")
                {
                    if (ext == "py")
                        md += string.Format("| Python3 | [short.py](short.py) | - | - |\n");
                    else
                        md += string.Format("| {0} | [short.{0}](short.{0}) | - | - |\n",ext);
                }
                else if (filename == "solution")
                {
                    if (ext == "py")
                        md += string.Format("| Python3 | - | [solution.py](solution.py) | - |\n");
                    else
                        md += string.Format("| {0} | - | [solution.{0}](solution.{0}) | - |\n", ext);
                }
                else if (filename == "submit")
                {
                    if (ext == "py")
                        md += string.Format("| Python3 | - | - | [submit.py](submit.py) |\n");
                    else
                        md += string.Format("| {0} | - | - | [submit.{0}](submit.{0}) |\n", ext);
                }
            }

            File.WriteAllText(dirs[i] + "\\README.md", md);
        }
    }
}
