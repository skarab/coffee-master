function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6364\" class=\"headerLeftMenuInActive\"><a id=\"aID6364\" href=\"#\" OnMouseOver=\"link('_dir','lightning0',this)\" class=\"leftMenuLinkHeadInActive\">lightning</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID868\" class=\"leftMenuInActive\"><a id=\"aID868\" href=\"#\" OnMouseOver=\"link('_class','FramePassLightning54809',this)\" class=\"leftMenuLinkInActive\">FramePassLightning</a></div>\n");
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
