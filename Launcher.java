import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.net.URISyntaxException;
import java.util.List;
import java.util.ArrayList;

public class Launcher {
	Launcher() {
		File dir = null;
		try {
			dir = new File(Launcher.class.getProtectionDomain().getCodeSource().getLocation().toURI()).getParentFile();
		} catch (URISyntaxException e1) {
			e1.printStackTrace();
		}
		
		FilenameFilter filter = new FilenameFilter() { 
			  
            public boolean accept(File f, String name) 
            { 
                return name.endsWith(".vpk"); 
            } 
        }; 
        
        final String path = dir.getPath();
        System.out.println(path);
        
        File[] vpks = dir.listFiles(filter); 
        
		JPanel panel = new JPanel(new BorderLayout());
		List<String> myList = new ArrayList<>();
		for (int i = 0; i < vpks.length; i++)  {
			myList.add(vpks[i].getName());
		}
		final JList<String> list = new JList<String>(myList.toArray(new String[myList.size()]));
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setViewportView(list);
		list.setLayoutOrientation(JList.VERTICAL);
		panel.add(scrollPane);
		JFrame frame = new JFrame("HLALauncher");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(panel);
		JButton button = new JButton("Start Map");
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	if(list.getSelectedValue() != null){
					try {
						Runtime.getRuntime().exec("cmd /c start cmd.exe /K " + path + "\\hlalauncher.exe " + path + "\\" + list.getSelectedValue());
						System.exit(0); 
					} catch (IOException e1) {
						e1.printStackTrace();
					}
				}
            }
        });
        panel.add(button, BorderLayout.SOUTH);
		frame.setSize(500, 800);
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
		
	}
	public static void main(String[] args) {
		new Launcher();
	}
}