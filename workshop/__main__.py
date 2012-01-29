import cgi
import os
import urllib2
import subprocess
import tempfile
import tornado.ioloop
import tornado.web

html = """
<html>
<head>
  <link rel="stylesheet" href="http://twitter.github.com/bootstrap/1.4.0/bootstrap.min.css">

  <script src="/cv/im/codemirror/lib/codemirror.js"></script>
  <link rel="stylesheet" href="/cv/im/codemirror/lib/codemirror.css">
  <script src="/cv/im/codemirror/mode/javascript/javascript.js"></script>
</head>
<body>
<div class="row">
    <img src="%(input_im)s"/>
    <img src="%(output_im)s"/>
</div>
<div class="row">
  <div class="span8">
    <pre>%(compiler_output)s</pre>
  </div>
  <div class="span8">
    <pre>%(execution_output)s</pre>
  </div>
</div>
<div class="row">
  <div class="span12">
    <form method="post" action="/cv">

      <div class="clearfix">
        <label for="url">URL</label>
        <div class="input">
          <input id="url" type="text" name="url" class="xxlarge" value="%(url)s"/>
        </div>
      </div>

      <div class="clearfix">
        <label for="code">Code</label>
        <div class="input">
          <textarea id="code" name="code" class="xxlarge">%(code)s</textarea>
        </div>
      </div>

      <div class="clearfix">
        <label for="code">Code</label>
        <div class="input">
          <input type="submit" name="submit"></input>
        </div>
      </div>
    </form>
  </div>
</div>
<script>
  var myCodeMirror = CodeMirror.fromTextArea(document.getElementById("code"));
</script>
</body>
</html>
"""

class MainHandler(tornado.web.RequestHandler):
    def get(self):
      url = "http://jungle.gradman.com/cv/im/static/monkey.jpg"
      input_im = output_im = ""
      compiler_output = execution_output = ""
      code = """output_im = cvCloneImage(input_im);"""
      self.write(html % locals())

    def post(self):
      url = self.get_argument("url")
      code = self.get_argument("code")

      # interpolate the code into the template
      with open("tmpl.cpp") as f:
        tmpl = f.read()
      maincpp = tmpl % code

      tempdir = tempfile.mkdtemp(dir="im")


      # write the code to disk
      with open(tempdir+"/main.cpp", "w") as f:
        f.write(maincpp)

      # compile and link the code
      try:
        compiler_output = subprocess.check_output(("g++ -c -o %(tempdir)s/main.o %(tempdir)s/main.cpp" % locals()).split(), stderr=subprocess.STDOUT)
      except subprocess.CalledProcessError, e:
        compiler_output = e.output

      try:
        compiler_output += subprocess.check_output(("g++ -lcv -lhighgui %(tempdir)s/main.o -o %(tempdir)s/main" % locals()).split(), stderr=subprocess.STDOUT)
      except subprocess.CalledProcessError, e:
        compiler_output += e.output

      # download the image
      image_data = urllib2.urlopen(url).read()
      with open(tempdir+"/in.jpg", "w") as f:
        f.write(image_data)

      input_im = tempdir+"/in.jpg"
      output_im = tempdir+"/out.jpg"
      # execute the code
      try:
        execution_output = subprocess.check_output(("%(tempdir)s/main %(tempdir)s/in.jpg %(tempdir)s/out.jpg" % locals()).split(), stderr=subprocess.STDOUT)
        os.chmod(tempdir, 0777)
        os.chmod(input_im, 0666)
        os.chmod(output_im, 0666)
      except subprocess.CalledProcessError, e:
        execution_output = e.output
      except OSError:
        execution_output = "did not execute"
      print "XXX", compiler_output

      for i in range(128, 255):
        compiler_output = compiler_output.replace(chr(i), "")
        execution_output = execution_output.replace(chr(i), "")

      execution_output = execution_output.replace("libdc1394 error: Failed to initialize libdc1394", "")
      compiler_output = cgi.escape(compiler_output)
      execution_output = cgi.escape(execution_output)
      
      input_im = "http://jungle.gradman.com/cv/"+input_im
      output_im = "http://jungle.gradman.com/cv/"+output_im
      self.write(html % locals())

application = tornado.web.Application([
    (r"/", MainHandler),
])

if __name__ == "__main__":
    application.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
