package main;

import java.awt.BorderLayout;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;

import org.jfree.*;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import jssc.SerialPort;
import jssc.SerialPortList;

public class Main{
	private static String CONNECT = "Connect";
	private static String DISCONNECT = "Disconnect";
	
	private static SerialCommChannel channel;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JFrame window = new JFrame();
		window.setTitle("Water Level Graph");
		window.setSize(600,400);
		
		window.setLayout(new BorderLayout());
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JComboBox<String> portList = new JComboBox<>();
		JButton connectButton = new JButton(CONNECT);
		
		connectButton.addActionListener(e->{
			JButton src = (JButton) e.getSource();
			if(src.getText().equals(CONNECT)) {
				
				src.setText(DISCONNECT);
			}
			else {
				
				src.setText(CONNECT);
			}
		});
		
		JPanel topPanel = new JPanel();
		topPanel.add(portList);
		topPanel.add(connectButton);

		window.add(topPanel,BorderLayout.NORTH);
		
		String[] ports = SerialPortList.getPortNames();
		for(int i = 0; i < ports.length; i++) {
			portList.addItem(ports[i]);
		}
		
		XYSeries data = new XYSeries("Sonar Sensor Readings");
		XYSeriesCollection dataset = new XYSeriesCollection(data);
		
		JFreeChart chart = ChartFactory.createXYLineChart("Water Level", "Time (seconds)" , "Height", dataset);
		
		
		
		
		
		window.add(new ChartPanel(chart), BorderLayout.CENTER);
		
		
		window.setVisible(true);
	}

}
