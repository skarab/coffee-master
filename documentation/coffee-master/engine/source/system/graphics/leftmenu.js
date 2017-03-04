function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6374\" class=\"headerLeftMenuInActive\"><a id=\"aID6374\" href=\"#\" OnMouseOver=\"link('_dir','graphics0',this)\" class=\"leftMenuLinkHeadInActive\">graphics</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6344\" class=\"leftMenuInActive\"><a id=\"aID6344\" href=\"#\" OnMouseOver=\"link('_dir','camera/camera0',this)\" class=\"leftMenuLinkInActive\">camera</a></div>\n");
document.write("<div id=\"divID6346\" class=\"leftMenuInActive\"><a id=\"aID6346\" href=\"#\" OnMouseOver=\"link('_dir','component/component0',this)\" class=\"leftMenuLinkInActive\">component</a></div>\n");
document.write("<div id=\"divID6355\" class=\"leftMenuInActive\"><a id=\"aID6355\" href=\"#\" OnMouseOver=\"link('_dir','device/device0',this)\" class=\"leftMenuLinkInActive\">device</a></div>\n");
document.write("<div id=\"divID6356\" class=\"leftMenuInActive\"><a id=\"aID6356\" href=\"#\" OnMouseOver=\"link('_dir','font/font0',this)\" class=\"leftMenuLinkInActive\">font</a></div>\n");
document.write("<div id=\"divID6501\" class=\"leftMenuInActive\"><a id=\"aID6501\" href=\"#\" OnMouseOver=\"link('_dir','frame/frame0',this)\" class=\"leftMenuLinkInActive\">frame</a></div>\n");
document.write("<div id=\"divID6372\" class=\"leftMenuInActive\"><a id=\"aID6372\" href=\"#\" OnMouseOver=\"link('_dir','gatherer/gatherer0',this)\" class=\"leftMenuLinkInActive\">gatherer</a></div>\n");
document.write("<div id=\"divID6373\" class=\"leftMenuInActive\"><a id=\"aID6373\" href=\"#\" OnMouseOver=\"link('_dir','geometric/geometric0',this)\" class=\"leftMenuLinkInActive\">geometric</a></div>\n");
document.write("<div id=\"divID6375\" class=\"leftMenuInActive\"><a id=\"aID6375\" href=\"#\" OnMouseOver=\"link('_dir','material/material0',this)\" class=\"leftMenuLinkInActive\">material</a></div>\n");
document.write("<div id=\"divID6376\" class=\"leftMenuInActive\"><a id=\"aID6376\" href=\"#\" OnMouseOver=\"link('_dir','mesh/mesh0',this)\" class=\"leftMenuLinkInActive\">mesh</a></div>\n");
document.write("<div id=\"divID6378\" class=\"leftMenuInActive\"><a id=\"aID6378\" href=\"#\" OnMouseOver=\"link('_dir','renderer/renderer0',this)\" class=\"leftMenuLinkInActive\">renderer</a></div>\n");
document.write("<div id=\"divID6380\" class=\"leftMenuInActive\"><a id=\"aID6380\" href=\"#\" OnMouseOver=\"link('_dir','shader/shader0',this)\" class=\"leftMenuLinkInActive\">shader</a></div>\n");
document.write("<div id=\"divID6382\" class=\"leftMenuInActive\"><a id=\"aID6382\" href=\"#\" OnMouseOver=\"link('_dir','sky/sky0',this)\" class=\"leftMenuLinkInActive\">sky</a></div>\n");
document.write("<div id=\"divID6385\" class=\"leftMenuInActive\"><a id=\"aID6385\" href=\"#\" OnMouseOver=\"link('_dir','texture/texture0',this)\" class=\"leftMenuLinkInActive\">texture</a></div>\n");
document.write("<div id=\"divID6386\" class=\"leftMenuInActive\"><a id=\"aID6386\" href=\"#\" OnMouseOver=\"link('_dir','viewport/viewport0',this)\" class=\"leftMenuLinkInActive\">viewport</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID881\" class=\"leftMenuInActive\"><a id=\"aID881\" href=\"#\" OnMouseOver=\"link('_class','Module54809',this)\" class=\"leftMenuLinkInActive\">Module</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
