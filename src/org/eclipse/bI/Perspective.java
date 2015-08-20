package org.eclipse.bI;

import org.eclipse.ui.IFolderLayout;
import org.eclipse.ui.IPageLayout;
import org.eclipse.ui.IPerspectiveFactory;
import org.eclipse.ui.console.IConsoleConstants;

public class Perspective implements IPerspectiveFactory {
	
	public static final String ID = "org.eclipse.bI.perspective";

	@Override
	public void createInitialLayout(IPageLayout layout) {
		defineActions(layout);
		defineLayout(layout);
	}

	private void defineActions(IPageLayout layout) {
		// views
		layout.addShowViewShortcut(IPageLayout.ID_PROJECT_EXPLORER);
		layout.addShowViewShortcut(IConsoleConstants.ID_CONSOLE_VIEW);
	}

	private void defineLayout(IPageLayout layout) {
		String editorArea = layout.getEditorArea();
		IFolderLayout left   = layout.createFolder("left", IPageLayout.LEFT, (float) 0.2, editorArea);
		IFolderLayout bottom = layout.createFolder("bottom", IPageLayout.BOTTOM, (float) 0.7, editorArea);
		left.addView(IPageLayout.ID_PROJECT_EXPLORER);
		bottom.addView(IConsoleConstants.ID_CONSOLE_VIEW);
	}

}
