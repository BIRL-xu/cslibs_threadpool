#include <opencv2/opencv.hpp>
#include <utils_threadpool/scheduling/task_scheduler.h>

void update(unsigned int row,
            cv::Mat &rows)
{
    for(unsigned int i = 0 ; i < 255 ; ++i) {
        rows.at<cv::Vec3b>(2*row,2*i)     = cv::Vec3b(row, i, 0);
        rows.at<cv::Vec3b>(2*row+1,2*i)   = cv::Vec3b(row, i, 0);
        rows.at<cv::Vec3b>(2*row,2*i+1)   = cv::Vec3b(row, i, 0);
        rows.at<cv::Vec3b>(2*row+1,2*i+1) = cv::Vec3b(row, i, 0);
        std::chrono::milliseconds dura( 1 );
        std::this_thread::sleep_for( dura );
    }
}


int main(int argc, char *argv[])
{
    cv::Mat m(510,510,CV_8UC3, cv::Scalar::all(0));

    TaskScheduler ts(4);

    /// STD
    for(unsigned int i = 0 ; i < 255 ; ++i) {
        std::function<void()> lambda = [i,&m](){update(i, m);};
        Task::Ptr task(new Task(lambda));
        ts.push(task);
    }

    while(ts.running()) {
        cv::Mat curr = m.clone();
        cv::imshow("test_threadpool_visual", curr);

        int key = cv::waitKey(10) & 0xFF;
        if(key == 27) {
            ts.shutdown();
            break;
        }
    }

    cv::imshow("test_threadpool_visual", m);
    cv::waitKey(0);

    ts.restart(4);

    /// APPEND
    m = cv::Mat(510,510,CV_8UC3, cv::Scalar::all(0));
    unsigned int appendix = 0;
    Task::Ptr chain;
    for(unsigned int i = 0 ; i < 255 ; ++i) {
        std::function<void()> lambda = [i,&m](){update(i, m);};
        Task::Ptr task(new Task(lambda));

        if(chain) {
            chain->append(task);

            if(appendix < 10) {
                ++appendix;
            } else {
                ts.push(chain);
                appendix = 0;
                chain.reset();
            }
        } else {
            chain = task;
        }
    }

    if(chain)
        ts.push(chain);

    while(ts.running()) {
        cv::Mat curr = m.clone();
        cv::imshow("test_threadpool_visual", curr);
        int key = cv::waitKey(10) & 0xFF;
        if(key == 27) {
            ts.shutdown();
            break;
        }
    }

    cv::imshow("test_threadpool_visual", m);
    cv::waitKey(0);

    return 0;
}
