function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6368\" class=\"headerLeftMenuInActive\"><a id=\"aID6368\" href=\"#\" OnMouseOver=\"link('_dir','transparent0',this)\" class=\"leftMenuLinkHeadInActive\">transparent</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID872\" class=\"leftMenuInActive\"><a id=\"aID872\" href=\"#\" OnMouseOver=\"link('_class','FramePassTransparent54809',this)\" class=\"leftMenuLinkInActive\">FramePassTransparent</a></div>\n");
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
