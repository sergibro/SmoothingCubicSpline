namespace SmoothingCubicSpline
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
			System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
			System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint1 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 4D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint2 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 1D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint3 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 0D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint4 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 1D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint5 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 4D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint6 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 9D);
			System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint7 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 4D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint8 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 1D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint9 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 0D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint10 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 1D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint11 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 4D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint12 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(0D, 9D);
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.rbLang = new System.Windows.Forms.RadioButton();
			this.bInfo = new System.Windows.Forms.Button();
			this.trackBarLambda = new System.Windows.Forms.TrackBar();
			this.chart = new System.Windows.Forms.DataVisualization.Charting.Chart();
			this.textBoxLambda = new System.Windows.Forms.TextBox();
			this.lLambda = new System.Windows.Forms.Label();
			this.bLoadFile = new System.Windows.Forms.Button();
			this.lFileName = new System.Windows.Forms.Label();
			this.bDetails = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.trackBarLambda)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.chart)).BeginInit();
			this.SuspendLayout();
			// 
			// rbLang
			// 
			this.rbLang.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.rbLang.BackColor = System.Drawing.Color.Transparent;
			this.rbLang.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.rbLang.Checked = true;
			this.rbLang.Location = new System.Drawing.Point(684, 12);
			this.rbLang.Name = "rbLang";
			this.rbLang.Size = new System.Drawing.Size(56, 33);
			this.rbLang.TabIndex = 1;
			this.rbLang.TabStop = true;
			this.rbLang.Text = "Eng";
			this.rbLang.UseVisualStyleBackColor = false;
			this.rbLang.Click += new System.EventHandler(this.rbLang_Click);
			// 
			// bInfo
			// 
			this.bInfo.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.bInfo.AutoSize = true;
			this.bInfo.Font = new System.Drawing.Font("Calibri", 14.25F);
			this.bInfo.ForeColor = System.Drawing.Color.Black;
			this.bInfo.Location = new System.Drawing.Point(564, 12);
			this.bInfo.Name = "bInfo";
			this.bInfo.Size = new System.Drawing.Size(114, 33);
			this.bInfo.TabIndex = 2;
			this.bInfo.Text = "Information";
			this.bInfo.UseVisualStyleBackColor = true;
			this.bInfo.Click += new System.EventHandler(this.bInfo_Click);
			// 
			// trackBarLambda
			// 
			this.trackBarLambda.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.trackBarLambda.Cursor = System.Windows.Forms.Cursors.VSplit;
			this.trackBarLambda.LargeChange = 50000;
			this.trackBarLambda.Location = new System.Drawing.Point(12, 480);
			this.trackBarLambda.Maximum = 100000;
			this.trackBarLambda.Name = "trackBarLambda";
			this.trackBarLambda.Size = new System.Drawing.Size(728, 45);
			this.trackBarLambda.TabIndex = 1;
			this.trackBarLambda.TickFrequency = 5;
			this.trackBarLambda.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBarLambda.Value = 90000;
			this.trackBarLambda.MouseCaptureChanged += new System.EventHandler(this.trackBarLambda_MouseCaptureChanged);
			// 
			// chart
			// 
			this.chart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.chart.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
			chartArea1.AxisX.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
			chartArea1.AxisX.MajorTickMark.TickMarkStyle = System.Windows.Forms.DataVisualization.Charting.TickMarkStyle.AcrossAxis;
			chartArea1.AxisY.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
			chartArea1.AxisY.MajorTickMark.TickMarkStyle = System.Windows.Forms.DataVisualization.Charting.TickMarkStyle.AcrossAxis;
			chartArea1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
			chartArea1.InnerPlotPosition.Auto = false;
			chartArea1.InnerPlotPosition.Height = 97F;
			chartArea1.InnerPlotPosition.Width = 95F;
			chartArea1.InnerPlotPosition.X = 5F;
			chartArea1.Name = "ChartAreaCurrent";
			this.chart.ChartAreas.Add(chartArea1);
			legend1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
			legend1.Font = new System.Drawing.Font("Calibri", 14F);
			legend1.IsTextAutoFit = false;
			legend1.Name = "LegendCurrent";
			legend1.Title = "Chart data";
			legend1.TitleFont = new System.Drawing.Font("Calibri", 14.25F);
			this.chart.Legends.Add(legend1);
			this.chart.Location = new System.Drawing.Point(12, 51);
			this.chart.Name = "chart";
			series1.ChartArea = "ChartAreaCurrent";
			series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
			series1.Color = System.Drawing.Color.Blue;
			series1.Legend = "LegendCurrent";
			series1.MarkerColor = System.Drawing.Color.Aqua;
			series1.MarkerSize = 3;
			series1.MarkerStyle = System.Windows.Forms.DataVisualization.Charting.MarkerStyle.Cross;
			series1.Name = "Data";
			dataPoint1.MarkerColor = System.Drawing.Color.Blue;
			dataPoint1.MarkerSize = 3;
			dataPoint1.MarkerStyle = System.Windows.Forms.DataVisualization.Charting.MarkerStyle.Cross;
			dataPoint2.MarkerColor = System.Drawing.Color.Blue;
			dataPoint2.MarkerSize = 3;
			dataPoint2.MarkerStyle = System.Windows.Forms.DataVisualization.Charting.MarkerStyle.Cross;
			dataPoint3.MarkerColor = System.Drawing.Color.Blue;
			dataPoint3.MarkerSize = 3;
			dataPoint3.MarkerStyle = System.Windows.Forms.DataVisualization.Charting.MarkerStyle.Cross;
			dataPoint4.MarkerColor = System.Drawing.Color.Blue;
			dataPoint4.MarkerSize = 3;
			dataPoint4.MarkerStyle = System.Windows.Forms.DataVisualization.Charting.MarkerStyle.Cross;
			dataPoint5.MarkerColor = System.Drawing.Color.Blue;
			dataPoint5.MarkerSize = 3;
			dataPoint5.MarkerStyle = System.Windows.Forms.DataVisualization.Charting.MarkerStyle.Cross;
			dataPoint6.MarkerBorderColor = System.Drawing.Color.Empty;
			dataPoint6.MarkerBorderWidth = 1;
			dataPoint6.MarkerColor = System.Drawing.Color.Blue;
			dataPoint6.MarkerSize = 3;
			dataPoint6.MarkerStyle = System.Windows.Forms.DataVisualization.Charting.MarkerStyle.Cross;
			series1.Points.Add(dataPoint1);
			series1.Points.Add(dataPoint2);
			series1.Points.Add(dataPoint3);
			series1.Points.Add(dataPoint4);
			series1.Points.Add(dataPoint5);
			series1.Points.Add(dataPoint6);
			series1.ShadowColor = System.Drawing.Color.Empty;
			series1.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
			series1.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
			series2.ChartArea = "ChartAreaCurrent";
			series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
			series2.Color = System.Drawing.Color.Red;
			series2.Legend = "LegendCurrent";
			series2.Name = "Spline";
			series2.Points.Add(dataPoint7);
			series2.Points.Add(dataPoint8);
			series2.Points.Add(dataPoint9);
			series2.Points.Add(dataPoint10);
			series2.Points.Add(dataPoint11);
			series2.Points.Add(dataPoint12);
			series2.ShadowColor = System.Drawing.Color.Transparent;
			series2.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
			series2.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
			this.chart.Series.Add(series1);
			this.chart.Series.Add(series2);
			this.chart.Size = new System.Drawing.Size(728, 423);
			this.chart.TabIndex = 4;
			// 
			// textBoxLambda
			// 
			this.textBoxLambda.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.textBoxLambda.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
			this.textBoxLambda.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.textBoxLambda.ForeColor = System.Drawing.Color.Yellow;
			this.textBoxLambda.Location = new System.Drawing.Point(98, 501);
			this.textBoxLambda.Name = "textBoxLambda";
			this.textBoxLambda.Size = new System.Drawing.Size(252, 31);
			this.textBoxLambda.TabIndex = 6;
			this.textBoxLambda.Text = "0.9";
			this.textBoxLambda.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxLambda.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxLambda_KeyDown);
			// 
			// lLambda
			// 
			this.lLambda.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.lLambda.BackColor = System.Drawing.Color.Transparent;
			this.lLambda.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
			this.lLambda.Location = new System.Drawing.Point(12, 503);
			this.lLambda.Name = "lLambda";
			this.lLambda.Size = new System.Drawing.Size(80, 25);
			this.lLambda.TabIndex = 7;
			this.lLambda.Text = "Lambda: ";
			// 
			// bLoadFile
			// 
			this.bLoadFile.ForeColor = System.Drawing.Color.Black;
			this.bLoadFile.Location = new System.Drawing.Point(12, 12);
			this.bLoadFile.Name = "bLoadFile";
			this.bLoadFile.Size = new System.Drawing.Size(150, 33);
			this.bLoadFile.TabIndex = 8;
			this.bLoadFile.Text = "Load File (.csv)";
			this.bLoadFile.UseVisualStyleBackColor = true;
			this.bLoadFile.Click += new System.EventHandler(this.bLoadFile_Click);
			// 
			// lFileName
			// 
			this.lFileName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.lFileName.BackColor = System.Drawing.Color.Green;
			this.lFileName.Location = new System.Drawing.Point(168, 12);
			this.lFileName.Name = "lFileName";
			this.lFileName.Size = new System.Drawing.Size(390, 33);
			this.lFileName.TabIndex = 9;
			this.lFileName.Text = "Chose File";
			this.lFileName.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// bDetails
			// 
			this.bDetails.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.bDetails.ForeColor = System.Drawing.Color.Black;
			this.bDetails.Location = new System.Drawing.Point(614, 427);
			this.bDetails.Name = "bDetails";
			this.bDetails.Size = new System.Drawing.Size(114, 33);
			this.bDetails.TabIndex = 10;
			this.bDetails.Text = "Details";
			this.bDetails.UseVisualStyleBackColor = true;
			this.bDetails.Click += new System.EventHandler(this.bDetails_Click);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 23F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
			this.ClientSize = new System.Drawing.Size(752, 537);
			this.Controls.Add(this.bDetails);
			this.Controls.Add(this.textBoxLambda);
			this.Controls.Add(this.lLambda);
			this.Controls.Add(this.lFileName);
			this.Controls.Add(this.bLoadFile);
			this.Controls.Add(this.chart);
			this.Controls.Add(this.trackBarLambda);
			this.Controls.Add(this.bInfo);
			this.Controls.Add(this.rbLang);
			this.Font = new System.Drawing.Font("Calibri", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.ForeColor = System.Drawing.Color.White;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Margin = new System.Windows.Forms.Padding(5);
			this.MinimumSize = new System.Drawing.Size(512, 384);
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Smoothing Cubic Spline";
			this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
			((System.ComponentModel.ISupportInitialize)(this.trackBarLambda)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.chart)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.RadioButton rbLang;
		private System.Windows.Forms.Button bInfo;
		private System.Windows.Forms.TrackBar trackBarLambda;
		private System.Windows.Forms.DataVisualization.Charting.Chart chart;
		private System.Windows.Forms.TextBox textBoxLambda;
		private System.Windows.Forms.Label lLambda;
		private System.Windows.Forms.Button bLoadFile;
		private System.Windows.Forms.Label lFileName;
		private System.Windows.Forms.Button bDetails;
	}
}

