using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SmoothingCubicSpline
{
	public partial class MainForm : Form
	{
		bool isEng = true;
		const string n = "\n", version = "1.0.0", name = "Labirint2D",
					 cpr = "Copyright ©  2017 Serhii Brodiuk";
		string fileName = ".csv";
		int pointsNum = 0;
		List<double> yRes = new List<double>();
		List<double> yData = new List<double>();
		List<double> xData = new List<double>();

		public MainForm()
		{
			InitializeComponent();
			chart.Series[0].Points.Clear();
			chart.Series[1].Points.Clear();
		}

		private void bLoadFile_Click(object sender, EventArgs e)
		{
			OpenFileDialog openFileDialog = new OpenFileDialog();

			openFileDialog.InitialDirectory = System.Reflection.Assembly.GetExecutingAssembly().GetName().CodeBase;
			openFileDialog.Filter = "csv files (*.csv)|*.csv|txt files (*.txt)|*.txt|All files (*.*)|*.*";
			openFileDialog.FilterIndex = 3;
			openFileDialog.RestoreDirectory = true;

			if (openFileDialog.ShowDialog() == DialogResult.OK)
			{
				try
				{
					if (openFileDialog.OpenFile().CanRead)
					{
						chart.Series[0].Points.Clear();
						chart.Series[1].Points.Clear();
						fileName = System.IO.Path.GetFullPath(openFileDialog.FileName); // openFileDialog.InitialDirectory + openFileDialog.FileName;
						lFileName.Text = System.IO.Path.GetFileNameWithoutExtension(openFileDialog.FileName);
						sbyte[] fn = new sbyte[fileName.Count()];
						for (int i = 0; i < fileName.Count(); ++i)
							fn[i] = (sbyte)fileName[i];
						unsafe
						{
							fixed (sbyte* cfileName = &fn[0])
							{
								CppWrapper.CppWrapperClass scs = new CppWrapper.CppWrapperClass(cfileName);
								double l = (double)scs.getLambda();
								textBoxLambda.Text = l.ToString();
								trackBarLambda.Value = (int)(l * trackBarLambda.Maximum);
								yRes = scs.yRes();
								yData = scs.y();
								xData = scs.x();
								pointsNum = xData.Count();
								if (pointsNum < 6) MessageBox.Show("Error: Number of points should be 6 and more.");
								else
								{
									for (int i = 0; i < yRes.Count; ++i)
									{
										chart.Series[0].Points.AddXY(xData[i], yData[i]);
										chart.Series[1].Points.AddXY(xData[i], yRes[i]);
									}
								}
							}
						}
					}
				}
				catch (Exception ex)
				{
					MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
				}
			}
		}

		private void textBoxLambda_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
			{
				//chart.Series[0].Points.Clear();
				chart.Series[1].Points.Clear();
				if (fileName.Count() < 5)
				{
					MessageBox.Show("Error: file not selected");
					return;
				}
				sbyte[] fn = new sbyte[fileName.Count()];
				for (int i = 0; i < fileName.Count(); ++i)
					fn[i] = (sbyte)fileName[i];
				double lambda;
				if (double.TryParse(textBoxLambda.Text, out lambda))
				{
					if (lambda < 0 || lambda > 1)
						textBoxLambda.Text = "lambda not in [0; 1]";
					else
					{
						unsafe
						{
							fixed (sbyte* cfileName = &fn[0])
							{
								CppWrapper.CppWrapperClass scs = new CppWrapper.CppWrapperClass(cfileName, lambda);
								double l = (double)scs.getLambda();
								textBoxLambda.Text = l.ToString();
								trackBarLambda.Value = (int)(l * trackBarLambda.Maximum);
								yRes = scs.yRes();
								for (int i = 0; i < yRes.Count; ++i)
								{
									//chart.Series[0].Points.AddXY(xData[i], yData[i]);
									chart.Series[1].Points.AddXY(xData[i], l == 1 ? yData[i] : yRes[i]);
								}
							}
						}
					}
				}
				else textBoxLambda.Text = "NaN";
			}
			if (e.KeyCode == Keys.Enter || e.KeyCode == Keys.Escape)
				//e.Handled = true;
				e.SuppressKeyPress = true;
		}

		private void trackBarLambda_MouseCaptureChanged(object sender, EventArgs e)
		{
			//chart.Series[0].Points.Clear();
			chart.Series[1].Points.Clear();
			if (fileName.Count() < 5)
			{
				MessageBox.Show("Error: file not selected");
				return;
			}
			sbyte[] fn = new sbyte[fileName.Count()];
			for (int i = 0; i < fileName.Count(); ++i)
				fn[i] = (sbyte)fileName[i];
			double lambda = (double)trackBarLambda.Value / trackBarLambda.Maximum;
			textBoxLambda.Text = lambda.ToString();
			unsafe
			{
				fixed (sbyte* cfileName = &fn[0])
				{
					CppWrapper.CppWrapperClass scs = new CppWrapper.CppWrapperClass(cfileName, lambda);
					yRes = scs.yRes();
					for (int i = 0; i < yRes.Count; ++i)
					{
						//chart.Series[0].Points.AddXY(xData[i], yData[i]);
						chart.Series[1].Points.AddXY(xData[i], lambda == 1 ? yData[i] : yRes[i]);
					}
				}
			}
		}

		private void bInfo_Click(object sender, EventArgs e)
		{
			MessageBox.Show(string.Concat(isEng ? "Program " : "Програма ", "\"Smoothing Cubic Spline\"", n, n,
												 isEng ? "Version " : "Версія ", version, n,
																					cpr, n,
isEng ? "Author: Brodiuk Serhii, Ukraine, Kyiv" : "Автор: Бродюк Сергій, Україна, м. Київ"),
							isEng ? "Information" : "Інформація",
							MessageBoxButtons.OK,
							MessageBoxIcon.Information,
							MessageBoxDefaultButton.Button3,
							MessageBoxOptions.RightAlign);
		}

		private void rbLang_Click(object sender, EventArgs e)
		{
			isEng = (rbLang.Text == "Укр"); // will change in next line
			rbLang.Text = isEng ? "Eng" : "Укр";
			rbLang.CheckAlign = isEng ? ContentAlignment.MiddleLeft : ContentAlignment.MiddleRight;
			bInfo.Text = isEng ? "Information" : "Інформація";
			bDetails.Text = isEng ? "Details" : "Деталі";
			bLoadFile.Text = isEng ? "Load File (.csv)" : "Зав. файл (.csv)";
			lLambda.Text = isEng ? "Lambda: " : "Лямбда: ";
			chart.Series[0].Name = isEng ? "Data" : "Дані";
			chart.Series[1].Name = isEng ? "Spline" : "Сплайн";
			chart.Legends[0].Title = isEng ? "Chart data" : "Дані графіка";
		}

		private void bDetails_Click(object sender, EventArgs e)
		{
			MessageBox.Show(string.Concat(isEng ? "Minimum points number is " : "Мінімальна кількість точок ", 5.ToString(), n,
isEng ? "" : ""),
							isEng ? "Details" : "Деталі",
							MessageBoxButtons.OK,
							MessageBoxIcon.Question,
							MessageBoxDefaultButton.Button3);
		}

	}
}
