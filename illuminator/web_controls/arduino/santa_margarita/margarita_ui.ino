void margarita_ui(EthernetClient cl){ 
cl.println("  <!DOCTYPE html> ");
cl.println("  <html>");
cl.println("      <head>");
cl.println("          <title>AxtonTech Illumnate the Night</title>");
cl.println("          <script>");
cl.println("        			_manualOff1 ='';");
cl.println("        			_lowBeam1 ='';");
cl.println("        			_highBeam1='';");
cl.println("        			_dayNight1='';");
cl.println("");
cl.println("        			_manualOff2 ='';");
cl.println("        			_lowBeam2 ='';");
cl.println("        			_highBeam2='';");
cl.println("        			_dayNight2='';");
cl.println("");
cl.println("        			_manualOff3 ='';");
cl.println("        			_lowBeam3 ='';");
cl.println("        			_highBeam3='';");
cl.println("        			_dayNight3='';");
cl.println("");
cl.println("            function XMLToString(oXML) {   ");
cl.println("                if (window.ActiveXObject) {     ");
cl.println("                    return oXML.xml;  //if IE ");
cl.println("                } else {     ");
cl.println("                    return (new XMLSerializer()).serializeToString(oXML);   ");
cl.println("                } ");
cl.println("            }");
cl.println("        		function GetArduinoIO()");
cl.println("        		{");
cl.println("        			nocache = '&nocache=' + Math.random() * 1000000;");

cl.println("      			var request = new XMLHttpRequest();");
cl.println("      			request.onreadystatechange = function()");
cl.println("      			{");


cl.println("      				if (this.readyState == 4) {");
cl.println("      					if(this.status == 200) {");
cl.println("      						if (this.responseXML != null) {");

if(digitalRead(io_jumper_illuminator1)==0 || digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('manualOff')[0].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm1.manualOff1.checked = true;");
  cl.println("							        } else { document.illuminatorForm1.manualOff1.checked = false;}");
}

if(digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('manualOff')[1].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm2.manualOff2.checked = true;");
  cl.println("							        } else { document.illuminatorForm2.manualOff2.checked = false;}");
}
if(digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('manualOff')[2].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm3.manualOff3.checked = true;");
  cl.println("							        } else { document.illuminatorForm3.manualOff3.checked = false;}");
}


if(digitalRead(io_jumper_illuminator1)==0 || digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("         							if (this.responseXML.getElementsByTagName('powerStatus')[0].childNodes[0].nodeValue === 'on') {");
  cl.println("      								document.getElementById('powerStatus1'     ).innerHTML = 'Illuminator Status on';");
  cl.println("                                                            }else{  document.getElementById('powerStatus1'     ).innerHTML = 'Illuminator Status off';}");
}
if(digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("         							if (this.responseXML.getElementsByTagName('powerStatus')[1].childNodes[0].nodeValue === 'on') {");
  cl.println("      								document.getElementById('powerStatus2'     ).innerHTML = 'Illuminator Status on';");
  cl.println("                                                            }else{  document.getElementById('powerStatus2'     ).innerHTML = 'Illuminator Status off';}");
}
if(digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("         							if (this.responseXML.getElementsByTagName('powerStatus')[2].childNodes[0].nodeValue === 'on') {");
  cl.println("      								document.getElementById('powerStatus3'     ).innerHTML = 'Illuminator Status on';");
  cl.println("                                                            }else{  document.getElementById('powerStatus3'     ).innerHTML = 'Illuminator Status off';}");
}
if(digitalRead(io_jumper_illuminator1)==0 || digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('lowBeamStatus')[0].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm1.lowBeam1.checked = true;");
  cl.println("							        } else { document.illuminatorForm1.lowBeam1.checked = false;}");
}
if(digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('lowBeamStatus')[1].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm2.lowBeam2.checked = true;");
  cl.println("							        } else { document.illuminatorForm2.lowBeam2.checked = false;}");
}
if(digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('lowBeamStatus')[2].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm3.lowBeam3.checked = true;");
  cl.println("							        } else { document.illuminatorForm3.lowBeam3.checked = false;}");
}

if(digitalRead(io_jumper_illuminator1)==0 || digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('highBeamStatus')[0].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm1.highBeam1.checked = true;");
  cl.println("							        } else { document.illuminatorForm1.highBeam1.checked = false;}");
}
if(digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('highBeamStatus')[1].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm2.highBeam2.checked = true;");
  cl.println("							        } else { document.illuminatorForm2.highBeam2.checked = false;}");
}
if(digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('highBeamStatus')[2].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm3.highBeam3.checked = true;");
  cl.println("							        } else { document.illuminatorForm3.highBeam3.checked = false;}");
}
if(digitalRead(io_jumper_illuminator1)==0 || digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('dayNightStatus')[0].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm1.dayNight1.checked = true;");
  cl.println("							        } else { document.illuminatorForm1.dayNight1.checked = false;}");
}
if(digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('dayNightStatus')[1].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm2.dayNight2.checked = true;");
  cl.println("							        } else { document.illuminatorForm2.dayNight2.checked = false;}");
}
if(digitalRead(io_jumper_illuminator3) == 0 ){
  cl.println("                                                            if (this.responseXML.getElementsByTagName('dayNightStatus')[2].childNodes[0].nodeValue === 'on') {");
  cl.println("								  document.illuminatorForm3.dayNight3.checked = true;");
  cl.println("							        } else { document.illuminatorForm3.dayNight3.checked = false;}");
}

cl.println("                                                    }");
cl.println("                                            }");
cl.println("                                     }");

cl.println("                            }");
cl.println("        			request.open('GET', 'ajax_inputs' + _manualOff1 + _manualOff2 + _manualOff3 + _lowBeam1 + _highBeam1 + _dayNight1 + _lowBeam2 + _highBeam2 + _dayNight2 + _lowBeam3 + _highBeam3 + _dayNight3 + nocache, true);");
cl.println("        			request.send(null);");
cl.println("        			setTimeout('GetArduinoIO()', 1000);");
cl.println("        			_manualOff1 ='';");
cl.println("        			_lowBeam1 ='';");
cl.println("        			_highBeam1='';");
cl.println("        			_dayNight1='';");
cl.println("");
cl.println("        			_manualOff2 ='';");
cl.println("        			_lowBeam2 ='';");
cl.println("        			_highBeam2='';");
cl.println("        			_dayNight2='';");
cl.println("");
cl.println("        			_manualOff3 ='';");
cl.println("        			_lowBeam3 ='';");
cl.println("        			_highBeam3='';");
cl.println("        			_dayNight3='';");
cl.println("");
cl.println("        		}");
cl.println("        ");
cl.println("    ");
cl.println("    ");
cl.println("        		function GetButtonManualOff1()");
cl.println("        		{");
cl.println("        			_manualOff1='&manualOff1=1';");
cl.println("        		}");
cl.println("        		function GetButtonLowBeam1()");
cl.println("        		{");
cl.println("        			_lowBeam1='&lowBeam1=1';");
cl.println("        		}");
cl.println("        		function GetButtonHighBeam1()");
cl.println("        		{");
cl.println("        			_highBeam1='&highBeam1=1';");
cl.println("        		}");
cl.println("        		function GetButtonDayNight1()");
cl.println("        		{");
cl.println("                           if (document.illuminatorForm1.dayNight1.checked === true){_dayNight1='&dayNight1=1';}else{_dayNight1='&dayNight1=0'}");
cl.println("        		}");
cl.println("");
cl.println("        		function GetButtonManualOff2()");
cl.println("        		{");
cl.println("        			_manualOff2='&manualOff2=1';");
cl.println("        		}");
cl.println("        		function GetButtonLowBeam2()");
cl.println("        		{");
cl.println("        			_lowBeam2='&lowBeam2=1';");
cl.println("        		}");
cl.println("        		function GetButtonHighBeam2()");
cl.println("        		{");
cl.println("        			_highBeam2='&highBeam2=1';");
cl.println("        		}");
cl.println("        		function GetButtonDayNight2()");
cl.println("        		{");
cl.println("                           if (document.illuminatorForm2.dayNight2.checked === true){_dayNight2='&dayNight2=1';}else{_dayNight2='&dayNight2=0'}");
cl.println("        		}");
cl.println("");
cl.println("        		function GetButtonManualOff3()");
cl.println("        		{");
cl.println("        			_manualOff3='&manualOff3=1';");
cl.println("        		}");
cl.println("        		function GetButtonLowBeam3()");
cl.println("        		{");
cl.println("        			_lowBeam3='&lowBeam3=1';");
cl.println("        		}");
cl.println("        		function GetButtonHighBeam3()");
cl.println("        		{");
cl.println("        			_highBeam3='&highBeam3=1';");
cl.println("        		}");
cl.println("        		function GetButtonDayNight3()");
cl.println("        		{");
cl.println("                           if (document.illuminatorForm3.dayNight3.checked === true){_dayNight3='&dayNight3=1';}else{_dayNight3='&dayNight3=0'}");
cl.println("        		}");
cl.println("        		");
cl.println("        		");
cl.println("  	      </script>");
cl.println("");
cl.println("  	<style>");
cl.println("  		.IO_box {");
cl.println("  			float  : left;");
cl.println("  			margin : 0 10px 25px 0;");
cl.println("  			border : 1px solid #73bc43;");
cl.println("  			padding: 0 5px 0 5px;");
cl.println("  			width  : 180px;");
cl.println("  		}");
cl.println("  		.h1 {");
cl.println("  			font-family: arial, sans-serif;font-size: 120%; ");
cl.println("  			color: #73bc43;");
cl.println("  			margin: 0 0 10px 0;");
cl.println("  		}");
cl.println("  		.h2 {");
cl.println("  			font-family: arial, sans-serif;font-size: 85%;");
cl.println("  			color: #73bc43;");
cl.println("  			margin: 5px 0 5px 0;");
cl.println("  		}");
cl.println("  		p, form, button {");
cl.println("  			font-size: 85%;");
cl.println("  			color: #252525;");
cl.println("  			");
cl.println("  			");
cl.println("  		}");
cl.println("  		.small_text {");
cl.println("  			font-size: 70%;");
cl.println("  			color: #737373;");
cl.println("  		}");
cl.println("            .powerRed{");
cl.println("  	            background-color:red;");
cl.println("  	            color:white;");
cl.println("  	        }");
cl.println("            .powerGreen{");
cl.println("  	            background-color:green;");
cl.println("  	            color:white;");
cl.println("  	        }");
cl.println("  	</style>");
cl.println("      </head>");
cl.println("");
cl.println("<img style='align:right' src='data:image/png;base64,");
  for (int i=0;i<21;i++){
    cl.write(logo_raw[i]);
  }
cl.println("'> ");                     
cl.println("<p>");
cl.println("      <body onload='GetArduinoIO()'>");
if(digitalRead(io_jumper_illuminator1)==0 || digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0 ){
cl.println("  		<div class='IO_box' >");
cl.println("");
  cl.println("          <span class='h1'>Illuminator #1</span>");
  cl.println("          <br/><br/>");
  cl.println("<form id='illuminator1' name='illuminatorForm1'>");
  cl.println("  				<input type='radio'  class='manualOff'    id='manualOff1'  name='manualOff1' value=0 onclick='GetButtonManualOff1 ()' ></button> Power Off<br />");
  cl.println("  				<input type='radio'  class='lowBeam'      id='lowBeam1'    name='lowBeam1'   value=0 onclick='GetButtonLowBeam1 ()'   ></button> Low Beam<br />");
  cl.println("  				<input type='radio'  class='highBeam'     id='highBeam1'   name='highBeam1'  value=0 onclick='GetButtonHighBeam1()'   ></button> High Beam<br />");
  cl.println("<hr>");
  cl.println("  				<input type='checkbox'  class='dayNight'  id='dayNight1'   name='dayNight1'  value=0 onclick='GetButtonDayNight1()'   ></button> D/N Switch Enable<br />");
  cl.println("  				<button type='button' class='powerStatus' id='powerStatus1'                                             >Illuminator Status off</button><br /><br/>");
  cl.println("  		</div>");
  cl.println("</form>");
}
cl.println("");
if(digitalRead(io_jumper_illuminator2) == 0 || digitalRead(io_jumper_illuminator3) == 0){
  cl.println("  		<div class='IO_box' >");
  cl.println("");
  cl.println("          <span class='h1'>Illuminator #2</span>");
  cl.println("          <br/><br/>");
  cl.println("<form id='illuminator2' name='illuminatorForm2'>");
  cl.println("  				<input type='radio'  class='manualOff'    id='manualOff2'   name='manualOff2'   value=0 onclick='GetButtonManualOff2 ()' ></button> Power Off<br />");
  cl.println("  				<input type='radio'  class='lowBeam'      id='lowBeam2'     name='lowBeam2'     value=0 onclick='GetButtonLowBeam2 ()'   ></button> Low Beam<br />");
  cl.println("  				<input type='radio'  class='highBeam'     id='highBeam2'    name='highBeam2'    value=0 onclick='GetButtonHighBeam2()'   ></button> High Beam<br />");
  cl.println("<hr>");
  cl.println("  				<input type='checkbox'  class='dayNight'  id='dayNight2'    name='dayNight2'    value=0 onclick='GetButtonDayNight2()'   ></button> D/N Switch Enable<br />");
  cl.println("  				<button type='button' class='powerStatus' id='powerStatus2'                                                      >Illuminator Status off</button><br /><br/>");
  cl.println("  		</div>");
  cl.println("</form>");
}
cl.println("");
if(digitalRead(io_jumper_illuminator3)==0){
  cl.println("  		<div class='IO_box' >");
  cl.println("");
  cl.println("          <span class='h1'>Illuminator #3</span>");
  cl.println("          <br/><br/>");
  cl.println("<form id='illuminator3' name='illuminatorForm3'>");
  cl.println("  				<input type='radio'  class='manualOff'   id='manualOff3'   name='manualOff3' value=0  onclick='GetButtonManualOff3 ()' ></button> Power Off<br />");
  cl.println("  				<input type='radio'  class='lowBeam'     id='lowBeam3'     name='lowBeam3'   value=0  onclick='GetButtonLowBeam3 ()'   ></button> Low Beam<br />");
  cl.println("  				<input type='radio'  class='highBeam'    id='highBeam3'    name='highBeam3'  value=0  onclick='GetButtonHighBeam3()'   ></button> High Beam<br />");
  cl.println("<hr>");
  cl.println("  				<input type='checkbox'  class='dayNight'    id='dayNight3'    name='dayNight3' onclick='GetButtonDayNight3()'  ></button> D/N Switch Enable<br />");
  cl.println("  				<button type='button' class='powerStatus' id='powerStatus3'                                                     >Illuminator Status off</button><br /><br/>");
  cl.println("  		</div>");
  cl.println("</form>");
}
cl.println("           ");
cl.println("      </body>");
cl.println("  </html>");
}

