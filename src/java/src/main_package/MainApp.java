package main_package;

import java.awt.BorderLayout;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JSlider;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import jssc.SerialPortList;

public class MainApp{
	private static String CONNECT = "Connect";
	private static String DISCONNECT = "Disconnect";
	private static String MANUAL_ON = "Manual ON";
	private static String MANUAL_OFF = "Manual OFF";
	private static double ALARM_THRESHOLD = 15.0;
	//private static String FAILURE = "Failure";
	
	private static SerialCommChannel channel;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JFrame window = new JFrame();
		window.setTitle("Water Level Graph");
		window.setSize(600,400);
		
		window.setLayout(new BorderLayout());
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JComboBox<String> portList = new JComboBox<>();
		
		String[] ports = SerialPortList.getPortNames();
		for(int i = 0; i < ports.length; i++) {
			portList.addItem(ports[i]);
		}
		JButton connectButton = new JButton(CONNECT);
		
		JPanel topPanel = new JPanel();
		topPanel.add(portList);
		topPanel.add(connectButton);
		
		JButton bBtn = new JButton(MANUAL_OFF);
		JSlider slider = new JSlider(0,1023,(int)1023/2);
		slider.setEnabled(false);
		
		JPanel bottomPanel = new JPanel();
		bottomPanel.add(bBtn);
		bottomPanel.add(slider);
		
		window.add(bottomPanel, BorderLayout.SOUTH);
		window.add(topPanel,BorderLayout.NORTH);

		
		XYSeries data = new XYSeries("Sonar Sensor Readings");
		XYSeriesCollection dataset = new XYSeriesCollection(data);
		
		JFreeChart chart = ChartFactory.createXYLineChart("Water Level", "Time (seconds)" , "Height", dataset);
		
		connectButton.addActionListener(e->{
			JButton src = (JButton) e.getSource();
			if(src.getText().equals(CONNECT)) {
				String selectedPort = portList.getSelectedItem().toString();
				try {
					channel = new SerialCommChannel(selectedPort,9600);
					System.out.println("Connected to: " + selectedPort);
					portList.setEnabled(false);
					src.setText(DISCONNECT);
				} catch (Exception e1) {
					System.out.println("There was an error with the port");
					System.exit(0);
					e1.printStackTrace();
				}
				/*Thread thread = new Thread(){
					int x = 0;
					@Override
					public void run() {
						try {
							String msg = channel.receiveMsg();
							double waterLevel = Double.parseDouble(msg);
							data.add(x++,waterLevel);
							
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
						
					}
				};
				thread.start();*/
			}
			else {
				channel.close();
				portList.setEnabled(true);
				src.setText(CONNECT);
			}
		});
		
		bBtn.addActionListener(al->{
			JButton btn = (JButton) al.getSource();
			
			if(btn.getText().equals(MANUAL_ON)) {
				slider.setEnabled(false);
				btn.setText(MANUAL_OFF);
			}
			else {
				slider.setEnabled(true);
				btn.setText(MANUAL_ON);
			}
		});
		

		
		
		
		
		
		window.add(new ChartPanel(chart), BorderLayout.CENTER);
		
		
		window.setVisible(true);
		
		int x = 0;
		
		while(true) {
			if(channel!=null) {
				try {
					String msg = channel.receiveMsg();
					if(msg!="") {
						double waterLevel = Double.parseDouble(msg);
						data.add(x++,waterLevel);
						if(waterLevel<=ALARM_THRESHOLD && slider.isEnabled()){
							channel.sendMsg(String.valueOf(slider.getValue()));
						}
					}
					
				} catch (InterruptedException e) {
					System.out.println("failed to receive in port");
					e.printStackTrace();
				}
			}
			else {
				System.out.println("channel was has not been setup");
			}
			
		}
	}

}
