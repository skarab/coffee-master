function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6366\" class=\"headerLeftMenuInActive\"><a id=\"aID6366\" href=\"#\" OnMouseOver=\"link('_dir','sky0',this)\" class=\"leftMenuLinkHeadInActive\">sky</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID870\" class=\"leftMenuInActive\"><a id=\"aID870\" href=\"#\" OnMouseOver=\"link('_class','FramePassSky54809',this)\" class=\"leftMenuLinkInActive\">FramePassSky</a></div>\n");
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
