function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6361\" class=\"headerLeftMenuInActive\"><a id=\"aID6361\" href=\"#\" OnMouseOver=\"link('_dir','ambient0',this)\" class=\"leftMenuLinkHeadInActive\">ambient</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID864\" class=\"leftMenuInActive\"><a id=\"aID864\" href=\"#\" OnMouseOver=\"link('_class','FramePassAmbient54809',this)\" class=\"leftMenuLinkInActive\">FramePassAmbient</a></div>\n");
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
