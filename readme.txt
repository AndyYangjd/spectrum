// This txt give the private data(contain data type) and Spec Class API

private data(contain type):
num		dataname			type			comment
1		fileName			string			the image name which you want to handle
2		path		    	string			the target directory where contain the image file(the file must be in this dir)
3		fileAdd				string			the full path of image file, so the OpenCV use this to open file
4		loadStatus		bool				judgement the status of read image:true for right, others wrong
5		srcFile				cv::Mat			CONSTANT, the grayscale value of source(src) image, 
6		sizeSrc				cv::Size2i	the size of src image, the same for srcCenFile
7		sizeDft				cv::size2i	the size of expadding the image for DFT
8		dftFile				cv::Mat			conserve values after srcFile's DFT and IDFT
9 	ReIm		vector<cv::Mat>		save the real and imaginary part after srcFile's DFT and IDFT
10	AmpPha	vector<cv::Mat>		get the amplitude and phase values
11	srcRect				cv::Rect		the Rect of srcFile

functions for initializing(default constration):
num	functionName		comment
1		loadImg				read,convert the image to grayscale,then load to srcFile, type is CV_8UC1
2		getSize				get image's size and save to sizeSrc

functions for DFT and IDFT:
num	functionName		comment
3		expadSize				get the expadding size and save to sizeDft
4		convtF					convert the srcFile type(CV_8UC1) to CV_32FC1,should not damage the srcFile
5		copyExpad				expad the copySrcFile to dftFile
6		centralize			centralize the dftFile
7		execDft					execute the DFT
8		getReIm					get the real and imaginary part after DFT
9		getAmpPha				get the amplitude and phase part after DFT


API(public functions):
num		functionName				comment
1		Spec						now the only construction
2		empty						judgement the read status, true for right, others wrong
3		getSizeSrc			get the src image size
4		showSizeSrc			show the src image size
5		getSizeDft			get the dftFile size
6		showSizeDft			show the dftFile size
7		getAmp 					get the amplitude value
8		getPha					get the phase value
9		saveAmp					save the amplitude
10	savePha					save the phase

