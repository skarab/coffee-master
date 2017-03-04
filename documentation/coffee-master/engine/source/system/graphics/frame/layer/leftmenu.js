function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6360\" class=\"headerLeftMenuInActive\"><a id=\"aID6360\" href=\"#\" OnMouseOver=\"link('_dir','layer0',this)\" class=\"leftMenuLinkHeadInActive\">layer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6358\" class=\"leftMenuInActive\"><a id=\"aID6358\" href=\"#\" OnMouseOver=\"link('_dir','bgra/bgra0',this)\" class=\"leftMenuLinkInActive\">bgra</a></div>\n");
document.write("<div id=\"divID6359\" class=\"leftMenuInActive\"><a id=\"aID6359\" href=\"#\" OnMouseOver=\"link('_dir','depth/depth0',this)\" class=\"leftMenuLinkInActive\">depth</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID863\" class=\"leftMenuInActive\"><a id=\"aID863\" href=\"#\" OnMouseOver=\"link('_class','FrameLayer54809',this)\" class=\"leftMenuLinkInActive\">FrameLayer</a></div>\n");
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
