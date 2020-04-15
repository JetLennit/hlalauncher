import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.net.URISyntaxException;
import java.text.SimpleDateFormat;

public class Launcher {
final int FRAME_WIDTH = 500;
final int FRAME_HEIGHT = 800;

	Launcher(){
		//get directory of jar
		File dir = null;
		try {
			dir = new File(Launcher.class.getProtectionDomain().getCodeSource().getLocation().toURI()).getParentFile();
		} catch (URISyntaxException e1) {
			e1.printStackTrace();
		}
		final String path = dir.getPath();

		//make a filter to find all vpks and then use it 
		FilenameFilter filter = new FilenameFilter() { 
			  
            public boolean accept(File f, String name) 
            { 
                return name.endsWith(".vpk"); 
            } 
		}; 
		File[] vpks = dir.listFiles(filter); 
		
		//create date formate
		SimpleDateFormat dateformat = new SimpleDateFormat("MM/dd/yyyy hh:mm a z");

		//fill table of vpks and adds labels
		Object[][] vpkrows = new Object[vpks.length][3];
		for (int i = 0; i < vpks.length; i++)  {
			vpkrows[i][0] = vpks[i].getName();
			vpkrows[i][1] = vpks[i].length()/(1024) + " kb";
			vpkrows[i][2] = dateformat.format(vpks[i].lastModified());
		}
		Object[] labels = {"Title", "Size", "Last Modified"};

		//make data displayable and prettier
		JTable vpktable = new JTable(vpkrows, labels);
		TableColumnModel columnmodel = vpktable.getColumnModel();
		columnmodel.getColumn(0).setPreferredWidth(FRAME_WIDTH/2);
		columnmodel.getColumn(1).setPreferredWidth(FRAME_WIDTH/4);
		columnmodel.getColumn(2).setPreferredWidth(FRAME_WIDTH/4);
		JScrollPane tablepane = new JScrollPane(vpktable);

		//initialize button
		JButton startbutton = new JButton("Start Map");

		//create jpanel and populate it
		JPanel panel = new JPanel(new BorderLayout());
		panel.add(tablepane);
		panel.add(startbutton, BorderLayout.SOUTH);

		//create the actual window
		JFrame frame = new JFrame("HLALauncher");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(panel);
		frame.setSize(FRAME_HEIGHT, FRAME_WIDTH);
		frame.setResizable(false);
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);

		//add action listener to button that launches the exe
		startbutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	if(vpktable.getValueAt(vpktable.getSelectedRow(), 0) != null){
					try {
						Runtime.getRuntime().exec("cmd /c start cmd.exe /K " + path + "\\hlalauncher.exe " + path + "\\" + vpktable.getValueAt(vpktable.getSelectedRow(), 0));
						System.exit(0); 
					} catch (IOException e1) {
						e1.printStackTrace();
					}
				}
            }
        });
	}
	public static void main(String[] args) {
		new Launcher();
	}
}