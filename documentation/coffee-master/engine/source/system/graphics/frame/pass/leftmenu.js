function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6363\" class=\"headerLeftMenuInActive\"><a id=\"aID6363\" href=\"#\" OnMouseOver=\"link('_dir','pass0',this)\" class=\"leftMenuLinkHeadInActive\">pass</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6361\" class=\"leftMenuInActive\"><a id=\"aID6361\" href=\"#\" OnMouseOver=\"link('_dir','ambient/ambient0',this)\" class=\"leftMenuLinkInActive\">ambient</a></div>\n");
document.write("<div id=\"divID6362\" class=\"leftMenuInActive\"><a id=\"aID6362\" href=\"#\" OnMouseOver=\"link('_dir','gbuffer/gbuffer0',this)\" class=\"leftMenuLinkInActive\">gbuffer</a></div>\n");
document.write("<div id=\"divID6364\" class=\"leftMenuInActive\"><a id=\"aID6364\" href=\"#\" OnMouseOver=\"link('_dir','lightning/lightning0',this)\" class=\"leftMenuLinkInActive\">lightning</a></div>\n");
document.write("<div id=\"divID6365\" class=\"leftMenuInActive\"><a id=\"aID6365\" href=\"#\" OnMouseOver=\"link('_dir','post_process/post_process0',this)\" class=\"leftMenuLinkInActive\">post_process</a></div>\n");
document.write("<div id=\"divID6366\" class=\"leftMenuInActive\"><a id=\"aID6366\" href=\"#\" OnMouseOver=\"link('_dir','sky/sky0',this)\" class=\"leftMenuLinkInActive\">sky</a></div>\n");
document.write("<div id=\"divID6367\" class=\"leftMenuInActive\"><a id=\"aID6367\" href=\"#\" OnMouseOver=\"link('_dir','tone_mapper/tone_mapper0',this)\" class=\"leftMenuLinkInActive\">tone_mapper</a></div>\n");
document.write("<div id=\"divID6368\" class=\"leftMenuInActive\"><a id=\"aID6368\" href=\"#\" OnMouseOver=\"link('_dir','transparent/transparent0',this)\" class=\"leftMenuLinkInActive\">transparent</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID866\" class=\"leftMenuInActive\"><a id=\"aID866\" href=\"#\" OnMouseOver=\"link('_class','FramePass54809',this)\" class=\"leftMenuLinkInActive\">FramePass</a></div>\n");
document.write("<div id=\"divID867\" class=\"leftMenuInActive\"><a id=\"aID867\" href=\"#\" OnMouseOver=\"link('_class','FramePassSystem54809',this)\" class=\"leftMenuLinkInActive\">FramePassSystem</a></div>\n");
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
