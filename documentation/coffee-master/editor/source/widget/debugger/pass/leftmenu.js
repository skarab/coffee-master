function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6483\" class=\"headerLeftMenuInActive\"><a id=\"aID6483\" href=\"#\" OnMouseOver=\"link('_dir','pass0',this)\" class=\"leftMenuLinkHeadInActive\">pass</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1093\" class=\"leftMenuInActive\"><a id=\"aID1093\" href=\"#\" OnMouseOver=\"link('_class','DebuggerPass22483',this)\" class=\"leftMenuLinkInActive\">DebuggerPass</a></div>\n");
document.write("<div id=\"divID6171\" class=\"leftMenuInActive\"><a id=\"aID6171\" href=\"#\" OnMouseOver=\"link('_class','FramePass0',this)\" class=\"leftMenuLinkInActive\">FramePass</a></div>\n");
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
