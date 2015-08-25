package org.eclipse.bI;

import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.jface.wizard.WizardPage;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.INewWizard;
import org.eclipse.ui.IWorkbench;

public class NewbI extends Wizard implements INewWizard  {
	
	public static final String NAME="bI project";
	public static final String INFO="Inherit new bI project from prototype system.";	

	@Override public void init(IWorkbench arg0, IStructuredSelection arg1) {}
	@Override public boolean performFinish() { return false; }
	@Override public boolean canFinish() { return true; }
	
	@Override public void addPages() {
		super.addPages();
		addPage(new page());
	}
	
	class page extends WizardPage {
		
		page() {
			super(NAME);
			setWindowTitle("New "+NAME);
			setTitle(NAME);
			setDescription(INFO);
		}

		private Composite container;
		private int XL=10,XT=121,Y=10,DY=30,LW=111,TW=333;
		
		@Override
		public void createControl(Composite par) {
			container = new Composite(par, SWT.NONE);
			Label Lname = new Label(container, SWT.NONE);
			Lname.setText("name:");
			Lname.setBounds(XL,Y,LW,20);
			Text Tname = new Text(container, SWT.BORDER);
			Tname.setText("ProjectName");
			Tname.setBounds(XT,Y,TW,20);
			Y+=DY;
			Label Lbranch = new Label(container, SWT.NONE);
			Lbranch.setText("branch:");
			Lbranch.setBounds(XL,Y,LW,20);
			Text Tbranch = new Text(container, SWT.BORDER);
			Tbranch.setText("https://github.com/ponyatov/Y/tree/master");
			Tbranch.setBounds(XT,Y,TW,20);
			Y+=DY;
			setControl(container);
			setPageComplete(true);
		}
		
		public boolean performFinish() {
			System.out.println("performFinish()");
			return true;
		}
		
	}

}
