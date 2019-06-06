using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.IO;

namespace IMAGE28BitText
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                GETPIXEL(openFileDialog1.FileName);
            }
        }

        private void GETPIXEL(string PATH)
        {
            int _for, __for;
            bool check = true;
            StringBuilder sb1 = new StringBuilder();
            StringBuilder sb2 = new StringBuilder();
            richTextBox1.Text = "";
            richTextBox2.Text = "";
            Image image = Image.FromFile(PATH);
            Bitmap bitmap = new Bitmap(image);
            Rectangle rect = new Rectangle(0, 0, bitmap.Width, bitmap.Height);
            Bitmap _bitmap = bitmap.Clone(rect, PixelFormat.Format4bppIndexed);
            for(_for = 0;_for < _bitmap.Height;_for++)
            {
                for(__for  = 0;__for < _bitmap.Width;__for++)
                {
                    if(ChkSky(bitmap.GetPixel(__for, _for).R, bitmap.GetPixel(__for, _for).G, bitmap.GetPixel(__for, _for).B) == 100)
                    {
                        if (check)
                        {
                            sb1.Append(GETNUM(_bitmap.GetPixel(__for, _for).R, _bitmap.GetPixel(__for, _for).G, _bitmap.GetPixel(__for, _for).B).ToString() + ", ");
                        }
                        else
                        {
                            sb2.Append(GETNUM(_bitmap.GetPixel(__for, _for).R, _bitmap.GetPixel(__for, _for).G, _bitmap.GetPixel(__for, _for).B).ToString() + ", ");
                        }
                    }
                    else
                    {
                        if (check)
                        {
                            sb1.Append(Convert.ToString(ChkSky(bitmap.GetPixel(__for, _for).R, bitmap.GetPixel(__for, _for).G, bitmap.GetPixel(__for, _for).B)) + ", ");
                        }
                        else
                        {
                            sb2.Append(Convert.ToString(ChkSky(bitmap.GetPixel(__for, _for).R, bitmap.GetPixel(__for, _for).G, bitmap.GetPixel(__for, _for).B)) + ", ");
                        }
                    }
                }
                check = !check;
            }
            richTextBox1.Text = sb1.ToString() + "[" + (_bitmap.Height / 2).ToString() + "][" + _bitmap.Width.ToString() + "]";
            richTextBox2.Text = sb2.ToString() + "[" + (_bitmap.Height / 2).ToString() + "][" + _bitmap.Width.ToString() + "]";
            File.WriteAllText(Path.GetFileNameWithoutExtension(PATH) + "_1.txt", richTextBox1.Text);
            File.WriteAllText(Path.GetFileNameWithoutExtension(PATH) + "_2.txt", richTextBox2.Text);
            _bitmap.Save("hi.bmp");
        }

        private int GETNUM(int r, int g, int b)
        {
            if (r == 0 && g == 0 && b == 0)
                return 0;
            if (r == 0 && g == 0 && b == 128)
                return 1;
            if (r == 0 && g == 128 && b == 0)
                return 2;
            if (r == 0 && g == 128 && b == 128)
                return 3;
            if (r == 128 && g == 0 && b == 0)
                return 4;
            if (r == 128 && g == 0 && b == 128)
                return 5;
            if (r == 128 && g == 128 && b == 0)
                return 6;
            if (r == 192 && g == 192 && b == 192)
                return 7;
            if (r == 128 && g == 128 && b == 128)
                return 8;
            if (r == 0 && g == 0 && b == 255)
                return 9;
            if (r == 0 && g == 255 && b == 0)
                return 10;
            if (r == 0 && g == 255 && b == 255)
                return 11;
            if (r == 255 && g == 0 && b == 0)
                return 12;
            if (r == 255 && g == 0 && b == 255)
                return 13;
            if (r == 255 && g == 255 && b == 0)
                return 14;
            if (r == 255 && g == 255 && b == 255)
                return 15;
            return -1;
        }

        private int ChkSky(int r, int g, int b)
        {
            if (r == 92 && g == 148 && b == 252) // SKY
                return 11;
            if (r == 255 && g == 174 && b == 201) // Block(?)
                return 16;
            return 100;
        }
    }
}
/*
0~42

43~127

128~212

213~255
*/