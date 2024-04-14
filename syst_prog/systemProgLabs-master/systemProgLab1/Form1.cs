using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.Design;

namespace systemProgLab1
{ 
    public partial class Form1 : Form
    {
        [DllImport("TransportDLL", CharSet = CharSet.Ansi)]
        static extern bool startApp();


        [DllImport("TransportDLL", CharSet = CharSet.Ansi)]
        static extern void startThread();

        [DllImport("TransportDLL", CharSet = CharSet.Ansi)]
        static extern void stopThread();

        [DllImport("TransportDLL", CharSet = CharSet.Ansi)]
        static extern void stopAllThreads();
            
        [DllImport("TransportDLL", CharSet = CharSet.Ansi)]
        static extern void sendMessage(int addr, StringBuilder sb);

        Process childProcess = null;


        public Form1()
        {
            InitializeComponent();
        }

        private void startButton_Click(object sender, EventArgs e)
        {  
            if (childProcess==null || childProcess.HasExited)
            {
                threadsBox.Items.Clear();
                childProcess = Process.Start("ZhuchkovConsoleApp.exe");

                threadsBox.Items.Add("main");             

            }
            else
            {
                int n = 0;
                try
                {
                    n = Int32.Parse(thredsPerCliccEdit.Text); 
                }
                catch 
                { }
 
                for (int i = 0; i < n; ++i)
                {
                    startThread();
                    if (threadsBox.Items.Count == 1)
                    {
                        threadsBox.Items.Add((threadsBox.Items.Count).ToString());
                        threadsBox.Items.Add("All threads");
                    }
                    else
                    {
                        threadsBox.Items.Insert(threadsBox.Items.Count - 1, (threadsBox.Items.Count - 1).ToString());
                    }
                             
                }         
            }

        }

        private void stopButton_Click(object sender, EventArgs e)
        {
            if (childProcess==null || childProcess.HasExited)
            {
                threadsBox.Items.Clear();
            }
            else
            {

                stopThread();

                if (threadsBox.Items.Count > 3)
                {
                    threadsBox.Items.RemoveAt(threadsBox.Items.Count - 2);
                }
                else if(threadsBox.Items.Count == 3)
                {
                    threadsBox.Items.RemoveAt(threadsBox.Items.Count - 1);
                    threadsBox.Items.RemoveAt(threadsBox.Items.Count - 1);
                }
                else
                {
                    threadsBox.Items.Clear();
                }
                    
            }
        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
            int index = threadsBox.SelectedIndex;
            string message = messageBox.Text;

            
            if (index == threadsBox.Items.Count - 1)
            {
                sendMessage(-1, new StringBuilder(message));
            }
            else
            {
                sendMessage(index, new StringBuilder(message));
            }
        }

    }
}
