#include<opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "opencv2/video.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "fstream"

using namespace cv;
using namespace std;






int main(){
	
	
	std::string image_path;
	std::cout << "enter the path of input  empty_image: ";
	std::cin >> image_path;
	cv::Mat img = cv::imread(image_path);      //It returns a matrix object


	if (img.empty()) {
		std::cout << "image not found" << endl;
		return -1;
	}


	

	cv::Mat gray_image1;
	cv::Mat corrected_image1;

	cvtColor(img,gray_image1,COLOR_BGR2GRAY); 
	





	vector<Point2f> pts_in1;
	vector<Point2f> pts_out1;


	pts_in1.push_back(Point2f(950,220));   ///to get the required points
    pts_in1.push_back(Point2f(280,1050));
   	pts_in1.push_back(Point2f(1550,1060));
   	pts_in1.push_back(Point2f(1250,200));



	pts_out1.push_back(Point2f(472, 52));
	pts_out1.push_back(Point2f(472, 830));
	pts_out1.push_back(Point2f(800, 830));
	pts_out1.push_back(Point2f(800, 52));


	Mat h1 = findHomography(pts_in1, pts_out1);


	warpPerspective(gray_image1, corrected_image1, h1, gray_image1.size());


	


	cv::Rect y(472,52,328,778);
	cv::Mat in1 = corrected_image1(y);

	



	string video_path;
	cout<< "enter the path of the video: ";
	cin >> video_path;

	waitKey(0);

	VideoCapture x(video_path);


	if(!x.isOpened()){
		cout << "video not found" << endl;
		return -1;
	}


	int framenum = 1;

	Mat u;

	while(1){

		cv::Mat f;
		x >> f;


	    if (f.empty()){
      		break;
      		return -1;
	    }

	    
	    

	    if(framenum%5==0){



			cv::Mat gray_image2;
			cv::Mat corrected_image2;



			cvtColor(f,gray_image2,COLOR_BGR2GRAY);


			vector<Point2f> pts_in2;
			vector<Point2f> pts_out2;

			pts_in2.push_back(Point2f(950,220));   ///to get the required points
   			pts_in2.push_back(Point2f(280,1050));
   			pts_in2.push_back(Point2f(1550,1060));
   			pts_in2.push_back(Point2f(1250,200));



			pts_out2.push_back(Point2f(472, 52));
			pts_out2.push_back(Point2f(472, 830));
			pts_out2.push_back(Point2f(800, 830));
			pts_out2.push_back(Point2f(800, 52));


			Mat h2 = findHomography(pts_in2, pts_out2);


			warpPerspective(gray_image2, corrected_image2, h2, gray_image2.size());

			cv::Rect x1 (472,52,328,778);
			cv::Mat in2 = corrected_image2(x1);








			cv::Mat gray_image3;
			cv::Mat corrected_image3;



			cvtColor(u,gray_image3,COLOR_BGR2GRAY);


			vector<Point2f> pts_in3;
			vector<Point2f> pts_out3;

			pts_in3.push_back(Point2f(950,220));   ///to get the required points
   			pts_in3.push_back(Point2f(280,1050));
   			pts_in3.push_back(Point2f(1550,1060));
   			pts_in3.push_back(Point2f(1250,200));



			pts_out3.push_back(Point2f(472, 52));
			pts_out3.push_back(Point2f(472, 830));
			pts_out3.push_back(Point2f(800, 830));
			pts_out3.push_back(Point2f(800, 52));


			Mat h3 = findHomography(pts_in3, pts_out3);


			warpPerspective(gray_image3, corrected_image3, h3, gray_image3.size());

			cv::Rect x2 (472,52,328,778);
			cv::Mat in3 = corrected_image3(x2);			




			Mat queue;
			Mat dynam;


			absdiff(in2,in1,queue);
			absdiff(in3,in2,dynam);


			int r = 328;
			int c = 778;
			int count1 = 0;
			int count2 = 0;

			for (int i = 0; i<r;i++){
				for (int j=0;j<c;j++){
					if(queue.at<uchar>(j,i)>20){
						count1 = count1+1;
					}
				}
			}

			for (int k1 = 0; k1<r;k1++){
				for (int k2=0;k2<c;k2++){
					if(dynam.at<uchar>(k2,k1)>10){
						count2 = count2+1;
					}
				}
			}

			float y;
			y = c*r;

			float p1;
			float p2;

			p1 = count1/y;
			p2 = count2/y;

			string s1 = to_string(framenum);
			string s2 = to_string(p1);
			string s3 = to_string(p2);


			cout << s1 +" "+s2+" "+s3 << endl;
			
			
		}

		u=f;
		framenum = framenum+1;	

	}
	
	return 0;
}
