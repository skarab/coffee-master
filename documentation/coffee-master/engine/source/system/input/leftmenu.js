function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6390\" class=\"headerLeftMenuInActive\"><a id=\"aID6390\" href=\"#\" OnMouseOver=\"link('_dir','input0',this)\" class=\"leftMenuLinkHeadInActive\">input</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6387\" class=\"leftMenuInActive\"><a id=\"aID6387\" href=\"#\" OnMouseOver=\"link('_dir','command/command0',this)\" class=\"leftMenuLinkInActive\">command</a></div>\n");
document.write("<div id=\"divID6388\" class=\"leftMenuInActive\"><a id=\"aID6388\" href=\"#\" OnMouseOver=\"link('_dir','config/config0',this)\" class=\"leftMenuLinkInActive\">config</a></div>\n");
document.write("<div id=\"divID6389\" class=\"leftMenuInActive\"><a id=\"aID6389\" href=\"#\" OnMouseOver=\"link('_dir','handler/handler0',this)\" class=\"leftMenuLinkInActive\">handler</a></div>\n");
document.write("<div id=\"divID6391\" class=\"leftMenuInActive\"><a id=\"aID6391\" href=\"#\" OnMouseOver=\"link('_dir','keyboard/keyboard0',this)\" class=\"leftMenuLinkInActive\">keyboard</a></div>\n");
document.write("<div id=\"divID6392\" class=\"leftMenuInActive\"><a id=\"aID6392\" href=\"#\" OnMouseOver=\"link('_dir','mouse/mouse0',this)\" class=\"leftMenuLinkInActive\">mouse</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID900\" class=\"leftMenuInActive\"><a id=\"aID900\" href=\"#\" OnMouseOver=\"link('_class','Device26233',this)\" class=\"leftMenuLinkInActive\">Device</a></div>\n");
document.write("<div id=\"divID901\" class=\"leftMenuInActive\"><a id=\"aID901\" href=\"#\" OnMouseOver=\"link('_class','DeviceButton26233',this)\" class=\"leftMenuLinkInActive\">DeviceButton</a></div>\n");
document.write("<div id=\"divID902\" class=\"leftMenuInActive\"><a id=\"aID902\" href=\"#\" OnMouseOver=\"link('_class','EventKey26233',this)\" class=\"leftMenuLinkInActive\">EventKey</a></div>\n");
document.write("<div id=\"divID903\" class=\"leftMenuInActive\"><a id=\"aID903\" href=\"#\" OnMouseOver=\"link('_class','EventMouse26233',this)\" class=\"leftMenuLinkInActive\">EventMouse</a></div>\n");
document.write("<div id=\"divID904\" class=\"leftMenuInActive\"><a id=\"aID904\" href=\"#\" OnMouseOver=\"link('_class','Module26233',this)\" class=\"leftMenuLinkInActive\">Module</a></div>\n");
document.write("<div id=\"divID905\" class=\"leftMenuInActive\"><a id=\"aID905\" href=\"#\" OnMouseOver=\"link('_class','System26233',this)\" class=\"leftMenuLinkInActive\">System</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6230\" class=\"leftMenuInActive\"><a id=\"aID6230\" href=\"#\" OnMouseOver=\"link('_member','EVENT4438767',this)\" class=\"leftMenuLinkInActive\">EVENT</a></div>\n");
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
