/*
 * 作者：康林(msn、email: kl222@126.com)
 *
 * 从摄像头（QCarmera）或者（Player）中捕获视频帧。
 * 注意：android后景摄像头捕获的视频翻转-90度，前景摄像头翻转90度。
 * 用法：
 *      QCamera m_Camera;
 *      m_Camera.setCaptureMode(QCamera::CaptureVideo);
 *      CCaptureVideoFrame videoFrame;
 *      videoFrame.setSource(&m_Camera);
 * 注册SLOT：
 *      connect(&videoFrame, SIGNAL(sigCaptureFrame(const QVideoFrame&)),
 *           SLOT(CaptureVideoFrame(const QVideoFrame&)));
 * 在SLOT 中 CaptureVideoFrame(const QVideoFrame&) 处理捕获到的视频帧。
 *
 * 示例代码：
 *   QList<QByteArray> device = QCamera::availableDevices();
 *   QList<QByteArray>::iterator it;
 *   for(it = device.begin(); it != device.end(); it++)
 *   {
 *       qDebug("Camera:%s", qPrintable(QCamera::deviceDescription(*it)));
 *   }
 *
 *   QCamera camera(QCamera::availableDevices().at(1));
 *   camera.setCaptureMode(QCamera::CaptureVideo);
 *   CFrmPlayer player;
 *   CCaptureVideoFrame captureVideoFrame;
 *   if(captureVideoFrame.setSource(&camera))
 *   {
 *       qDebug("probe.setSource is ok");
 *       player.connect(&captureVideoFrame, SIGNAL(CaptureFrame(QVideoFrame)),
 *                      SLOT(present(QVideoFrame)));
 *   }
 *
 *   player.show();
 *   player.activateWindow();
 *   camera.start();
 */

#ifndef CAPTUREVIDEOFRAME_H
#define CAPTUREVIDEOFRAME_H

#include <QAbstractVideoSurface>
#include <QVideoProbe>
#include <QCamera>

class CCamera;
class CCaptureVideoFrame : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit CCaptureVideoFrame(CCamera* pCamera = NULL, QObject *parent = 0);
    virtual ~CCaptureVideoFrame();

    //设置捕获源
    bool setSource(QCamera *pCamera);
    //设置支持的捕获格式
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    //bool isFormatSupported(const QVideoSurfaceFormat &format) const;

signals:
    //从摄像头捕获的原始帧  
    void sigCaptureFrame(const QVideoFrame &frame);

private slots:
    virtual bool present(const QVideoFrame &frame);

private:
     QVideoProbe m_Probe;//android下,目前只能用probe捕获视频  
     CCamera *m_pCamera;
};

#endif // CAPTUREVIDEOFRAME_H
