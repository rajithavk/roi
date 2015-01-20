#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem/convenience.hpp>

using namespace boost::filesystem;

using namespace std;
using namespace cv;




int main(){

	path targetDir("img");

	directory_iterator it(targetDir), eod;

	BOOST_FOREACH(path const &p, make_pair(it, eod))
	{
	    if(is_regular_file(p))
	    {
	    			Mat image = imread(p.string(),0);
	    			//Mat image(image1.size(),image1.type());
	    			//cvtColor(image1,image,CV_BGR2GRAY);
	    			Mat bin(image.size(),image.type());
	    			threshold(image,bin,150,255,CV_THRESH_BINARY);
	    			Mat element = getStructuringElement( 0, Size( 25,25 ), Point( 2,2 ) );
	    			morphologyEx(bin,bin,MORPH_CLOSE,element);
	    			morphologyEx(bin,bin,MORPH_ERODE,element);
	    			element = getStructuringElement( 2, Size( 10,10 ), Point( 2,2 ) );
	    			morphologyEx(bin,bin,MORPH_OPEN,element);
	    			morphologyEx(bin,bin,MORPH_DILATE,element);
	    			Mat inv = Scalar::all(255) - bin;
	    			Mat res(image.size(),image.type());
	    			image.copyTo(res,bin);
	    			namedWindow("Output");
	    			imshow("bin",res);
	    			waitKey(0);
	    }
	}

    return 0;


}
